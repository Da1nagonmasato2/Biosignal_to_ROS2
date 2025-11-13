import os
os.environ["LSL_FORCE_IPV4"] = "1"  # IPv6警告回避

import dxcam
import numpy as np
import cv2
import time
from pylsl import StreamInfo, StreamOutlet

# ==== ROI設定 ====
x_min, y_min, x_max, y_max = 92, 190, 726, 266
origin = (y_max - y_min) / 2  # 中央基準
max_voltage = 1.5              # ±1.5Vレンジ
x_range_max = 50

# ==== dxcam初期化 ====
camera = dxcam.create(output_color="RGB")
roi = (x_min, y_min, x_max, y_max)
camera.start(region=roi, target_fps=30)

# ==== LSLストリーム初期化 ====
info = StreamInfo(
    name='EMG_Stream',
    type='EMG',
    channel_count=1,
    nominal_srate=30,
    channel_format='float32',
    source_id='emg_dxcam_peakabs'
)
outlet = StreamOutlet(info)
print("✅ LSLストリーム準備完了: EMG_Stream")

prev_frame = None
prev_time = time.time()

print("\nリアルタイムEMGピーク送信開始 (Ctrl+Cで終了)\n")

try:
    while True:
        frame = camera.get_latest_frame()
        if frame is None:
            time.sleep(0.001)
            continue

        # ==== グレースケール変換・二値化 ====
        img = cv2.cvtColor(frame, cv2.COLOR_RGB2GRAY)
        _, img_otsu = cv2.threshold(img, 0, 255, cv2.THRESH_OTSU)

        # ==== 差分検出 ====
        if prev_frame is not None:
            diff = cv2.absdiff(img_otsu, prev_frame)
            diff_binary = cv2.threshold(diff, 50, 255, cv2.THRESH_BINARY)[1]
        else:
            diff_binary = np.zeros_like(img_otsu)
        prev_frame = img_otsu.copy()

        # ==== EMG値計算（最大・最小ピーク検出）====
        ys_diff, xs_diff = np.where(diff_binary == 255)
        if len(xs_diff) > 0:
            x_min_line = np.min(xs_diff)
            x_max_line = np.max(xs_diff) - 1

            if x_max_line - x_min_line < x_range_max:
                mask_x = np.zeros_like(img_otsu, dtype=bool)
                mask_x[:, x_min_line:x_max_line + 1] = True
                ys_line, _ = np.where((img_otsu > 127) & mask_x)

                if len(ys_line) > 0:
                    # ==== 最大・最小検出 ====
                    y_peak = np.min(ys_line)
                    y_bottom = np.max(ys_line)

                    # ==== ピクセル → 電圧変換（中央基準 ±1.5V）====
                    emg_val_peak = max_voltage * (origin - y_peak) / origin
                    emg_val_bottom = max_voltage * (origin - y_bottom) / origin

                    # ==== 絶対値で比較して大きい方を採用 ====
                    if abs(emg_val_peak) >= abs(emg_val_bottom):
                        emg_val = emg_val_peak
                    else:
                        emg_val = emg_val_bottom
                else:
                    emg_val = 0.0
        else:
            emg_val = 0.0

        # ==== LSL送信 ====
        outlet.push_sample([emg_val])

        # ==== デバッグ出力 ====
        current_time = time.time()
        dt = current_time - prev_time
        prev_time = current_time
        rate = 1.0 / dt if dt > 0 else 0.0
        print(f"\rEMG: {emg_val:+.3f} V | {rate:4.1f} Hz", end="")

        time.sleep(0.005)

except KeyboardInterrupt:
    print("\n終了しました。")

finally:
    camera.stop()
    print("✅ 終了しました。")
