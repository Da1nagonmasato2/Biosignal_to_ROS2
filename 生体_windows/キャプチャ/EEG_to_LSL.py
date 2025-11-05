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
x_min, x_max = 2940, 2950
y_offsets = [82, 82 + 421, 82 + 844, 82 + 1264]  # A, B, C, D
max_voltage = 200.0
channels = ["A", "B", "C", "D"]

# ==== キャプチャ範囲を全体でカバー ====
y_min_all = y_offsets[0]
y_max_all = y_offsets[-1] + graph_height

# ==== 対象ウィンドウを取得 ====
hwnd = win32gui.FindWindow(None, TARGET_TITLE)
if hwnd == 0:
    raise Exception(f"ウィンドウ '{TARGET_TITLE}' が見つかりません。")

# ウィンドウを左上に移動
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
print("dxcam: 非同期キャプチャ開始")

# ==== LSLストリーム設定 ====
stream_name = "EEG_stream"
stream_type = "EEG"
n_channels = len(channels)
sample_rate = 30
info = StreamInfo(stream_name, stream_type, n_channels, sample_rate, 'float32', 'emg_dxcam_001')

ch_names_xml = ''.join([f"<channel><label>{ch}</label><unit>microvolts</unit></channel>" for ch in channels])
info.desc().append_child("channels").append_child_value("labels", ",".join(channels))
info.desc().append_child("desc").append_child_value("manufacturer", "dxcam_capture")

outlet = StreamOutlet(info)
print(f"LSLストリームを開始: {stream_name} ({n_channels}ch)")

print("\nEMGグラフ (A, B, C, D) の解析開始 (Ctrl+Cで終了)\n")

try:
    last_time = time.time()
    frame_count = 0

    while True:
        # ==== 非同期バッファから最新フレームを取得 ====
        frame_full = cam.get_latest_frame()
        if frame_full is None:
            print("\n⚠ キャプチャ失敗（ウィンドウが非表示？）")
            time.sleep(0.05)
            continue

        gray_full = cv2.cvtColor(frame_full, cv2.COLOR_RGB2GRAY)

        results = []
        vis_rows = []

        for ch_name, y_min_local in zip(channels, y_offsets):
            y0 = y_min_local - y_min_all
            y1 = y0 + graph_height
            y_center = graph_height / 2

            roi_gray = gray_full[y0:y1, :]
            roi_inv = cv2.bitwise_not(roi_gray)
            _, roi_bin = cv2.threshold(roi_inv, 0, 255, cv2.THRESH_BINARY + cv2.THRESH_OTSU)

            read_col = x_max - x_min - 1
            col_pixels = roi_bin[:, read_col]
            ys = np.where(col_pixels == 255)[0]

            if len(ys) > 0:
                y_mean = np.mean(ys)
                emg_val = -max_voltage * ((y_mean - y_center) / y_center)
            else:
                y_mean = -1
                emg_val = 0.0

            results.append((ch_name, y_mean, emg_val))

            vis = cv2.cvtColor(roi_bin, cv2.COLOR_GRAY2BGR)
            cv2.line(vis, (read_col, 0), (read_col, vis.shape[0]), (0, 0, 255), 1)
            cv2.line(vis, (0, int(y_center)), (vis.shape[1], int(y_center)), (255, 0, 0), 1)
            cv2.putText(vis, f"CH {ch_name}", (5, 20),
                        cv2.FONT_HERSHEY_SIMPLEX, 0.6, (0, 255, 0), 1)
            vis_rows.append(np.hstack((cv2.cvtColor(roi_gray, cv2.COLOR_GRAY2BGR), vis)))

        emg_values = [emg for _, _, emg in results]
        outlet.push_sample(emg_values)

        frame_count += 1
        now = time.time()
        elapsed = now - last_time
        fps = None
        if elapsed >= 1.0:
            fps = frame_count / elapsed
            frame_count = 0
            last_time = now

        msg = "\r" + " ".join([f"{ch}: EMG={emg:+7.2f}μV" for ch, _, emg in results])
        if fps:
            msg += f" | FPS={fps:4.1f}"
        print(msg, end="")

        combined = np.vstack(vis_rows)
        cv2.imshow("EMG Capture (左=原画像 / 右=検出結果)", combined)

        if cv2.waitKey(1) & 0xFF == 27:
            break

        time.sleep(0.05)

except KeyboardInterrupt:
    print("\n終了しました。")
finally:
    cv2.destroyAllWindows()
    cam.stop()
