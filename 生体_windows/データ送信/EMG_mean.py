import os
os.environ["LSL_FORCE_IPV4"] = "1"  # IPv6 警告回避

import dxcam
import cv2
import numpy as np
import time
import win32gui
import win32con
from pylsl import StreamInfo, StreamOutlet

# ==== 対象ウィンドウのタイトル ====
TARGET_TITLE = "ロジカルプロダクト ワイヤレスセンサモジュール Ver7.8.01_LP"

# ==== ROI設定 ====
x_min, y_min, x_max, y_max = 92, 190, 726, 266
origin = (y_max - y_min) / 2       # ROI中央
max_voltage = 1.5                  # ±1.5Vレンジ
x_range_max = 50

# ==== ウィンドウハンドル取得 ====
hwnd = win32gui.FindWindow(None, TARGET_TITLE)
if hwnd == 0:
    raise Exception(f"ウィンドウ '{TARGET_TITLE}' が見つかりません。")

win32gui.SetWindowPos(hwnd, win32con.HWND_TOP, 0, 0, 800, 600, 0)
print(f"ウィンドウ '{TARGET_TITLE}' を画面左上に移動しました。")

# ==== dxcam 初期化 ====
cam = dxcam.create(output_idx=0)
cam.start(target_fps=30)

# ==== LSLストリーム初期化 ====
info = StreamInfo(
    name='EMG_Stream',
    type='EMG',
    channel_count=1,
    nominal_srate=30,
    channel_format='float32',
    source_id='emg_dxcam_mean'
)
outlet = StreamOutlet(info)
print("✅ LSLストリーム準備完了: EMG_Stream")

prev_frame = None
prev_time = time.time()

print("\nリアルタイムEMG平均値送信開始 (Ctrl+Cで終了)\n")

try:
    while True:
        # ==== 最新フレーム取得 ====
        frame_full = cam.get_latest_frame()
        if frame_full is None:
            time.sleep(0.005)
            continue

        # ==== ウィンドウ位置を基準にROI抽出 ====
        try:
            wx1, wy1, wx2, wy2 = win32gui.GetWindowRect(hwnd)
            roi = frame_full[wy1 + y_min:wy1 + y_max, wx1 + x_min:wx1 + x_max]
        except Exception:
            continue

        if roi.size == 0:
            continue

        # ==== グレースケール・二値化 ====
        img = cv2.cvtColor(roi, cv2.COLOR_BGR2GRAY)
        _, img_otsu = cv2.threshold(img, 0, 255, cv2.THRESH_OTSU)

        # ==== 差分検出 ====
        if prev_frame is not None:
            diff = cv2.absdiff(img_otsu, prev_frame)
            diff_binary = cv2.threshold(diff, 50, 255, cv2.THRESH_BINARY)[1]
        else:
            diff_binary = np.zeros_like(img_otsu)
        prev_frame = img_otsu.copy()

        # ==== EMG値計算（平均値で ±1.5Vスケール）====
        ys_diff, xs_diff = np.where(diff_binary == 255)
        if len(xs_diff) > 0:
            x_min_line = np.min(xs_diff)
            x_max_line = np.max(xs_diff) - 1

            if x_max_line - x_min_line < x_range_max:
                mask_x = np.zeros_like(img_otsu, dtype=bool)
                mask_x[:, x_min_line:x_max_line + 1] = True
                ys_line, _ = np.where((img_otsu > 127) & mask_x)

                if len(ys_line) > 0:
                    y_mean = np.mean(ys_line)   # 平均値
                    # ★ 中央基準で ±1.5V にスケーリング
                    emg_val = max_voltage * (origin - y_mean) / origin
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
        rate = 1.0 / dt if dt > 0 else 0
        print(f"\rEMG: {emg_val:+.3f} V | {rate:4.1f} Hz", end="")

        time.sleep(0.005)

except KeyboardInterrupt:
    print("\n終了しました。")

finally:
    cam.stop()
    print("✅ 終了")
