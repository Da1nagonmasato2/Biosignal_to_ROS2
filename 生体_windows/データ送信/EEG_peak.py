import cv2
import numpy as np
import time
import win32gui
import win32con
import dxcam
from pylsl import StreamInfo, StreamOutlet

# ==== 対象ウィンドウのタイトル ====
TARGET_TITLE = "EmotivPRO 4.8.10.593"

# ==== グラフ設定 ====
graph_height = 442
x_min, x_max = 2900, 2950
y_offsets = [82, 82 + 421, 82 + 844, 82 + 1264]  # A, B, C, D
max_voltage = 200.0
channels = ["A", "B", "C", "D"]

y_min_all = y_offsets[0]
y_max_all = y_offsets[-1] + graph_height

# ==== 対象ウィンドウを取得 ====
hwnd = win32gui.FindWindow(None, TARGET_TITLE)
if hwnd == 0:
    raise Exception(f"ウィンドウ '{TARGET_TITLE}' が見つかりません。")

win32gui.SetWindowPos(hwnd, win32con.HWND_TOP, 0, 0, 3072, 1920, 0)
print(f"ウィンドウ '{TARGET_TITLE}' を画面左上に移動しました。")

# ==== dxcam初期化 ====
try:
    cam = dxcam.create(output_color="RGB")
    print("dxcam: GPUモードでキャプチャ開始")
except Exception:
    print("dxcam: GPUが使用できないためCPUモードに切替")
    cam = dxcam.create(output_color="RGB", device_idx=0)

# ==== 非同期キャプチャ開始 ====
cam.start(region=(x_min, y_min_all, x_max, y_max_all), target_fps=30)

# ==== LSLストリーム設定 ====
stream_name = "EEG_stream"
stream_type = "EEG"
n_channels = len(channels)
sample_rate = 30
info = StreamInfo(stream_name, stream_type, n_channels, sample_rate, 'float32', 'emg_dxcam_peak')
info.desc().append_child("channels").append_child_value("labels", ",".join(channels))
outlet = StreamOutlet(info)

print(f"LSLストリームを開始: {stream_name} ({n_channels}ch)")
print("EMGピーク値送信を開始 (Ctrl+Cで停止)\n")

try:
    last_time = time.time()
    frame_count = 0

    while True:
        frame_full = cam.get_latest_frame()
        if frame_full is None:
            time.sleep(0.01)
            continue

        gray_full = cv2.cvtColor(frame_full, cv2.COLOR_RGB2GRAY)
        emg_values = []

        for y_min_local in y_offsets:
            y0 = y_min_local - y_min_all
            y1 = y0 + graph_height
            y_center = graph_height / 2

            roi_gray = gray_full[y0:y1, :]
            roi_inv = cv2.bitwise_not(roi_gray)
            _, roi_bin = cv2.threshold(roi_inv, 0, 255, cv2.THRESH_BINARY + cv2.THRESH_OTSU)

            col_pixels = roi_bin[:, -1]  # 右端列を観測
            ys = np.where(col_pixels == 255)[0]

            if len(ys) > 0:
                y_peak = np.min(ys)
                emg_val = -max_voltage * ((y_peak - y_center) / y_center)
            else:
                emg_val = 0.0

            emg_values.append(emg_val)

        outlet.push_sample(emg_values)

        frame_count += 1
        now = time.time()
        if now - last_time >= 1.0:
            fps = frame_count / (now - last_time)
            print(f"\r送信FPS: {fps:.1f} | EMG={['%.1f' % v for v in emg_values]}", end="")
            frame_count = 0
            last_time = now

        time.sleep(0.02)

except KeyboardInterrupt:
    print("\n終了しました。")

finally:
    cam.stop()
