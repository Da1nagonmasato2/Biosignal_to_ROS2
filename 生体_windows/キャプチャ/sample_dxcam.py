import dxcam
import cv2
import numpy as np
import time
import win32gui
import win32con
import matplotlib.pyplot as plt
from collections import deque

TARGET_TITLE = "ロジカルプロダクト ワイヤレスセンサモジュール Ver7.8.01_LP"

x_min, y_min, x_max, y_max = 92, 190, 726, 266
origin = 78
max_voltage = 0.05
x_range_max = 50

MAX_POINTS = 300
emg_values = deque([0.0] * MAX_POINTS, maxlen=MAX_POINTS)

hwnd = win32gui.FindWindow(None, TARGET_TITLE)
if hwnd == 0:
    raise Exception(f"ウィンドウ '{TARGET_TITLE}' が見つかりません。")

win32gui.SetWindowPos(hwnd, win32con.HWND_TOP, 0, 0, 800, 600, 0)
print(f"ウィンドウ '{TARGET_TITLE}' を画面左上に移動しました。")

# ==== dxcam 初期化（colorはBGRで出る）====
cam = dxcam.create(output_idx=0)
cam.start(target_fps=30)  # 引数最小限でOK

plt.ion()
fig, ax = plt.subplots(figsize=(8, 3))
(line,) = ax.plot(emg_values, color="lime")
ax.set_ylim(-max_voltage, max_voltage)
ax.set_xlim(0, MAX_POINTS)
ax.set_xlabel("Time (frames)")
ax.set_ylabel("EMG Voltage (V)")
ax.grid(True)

prev_frame = None
prev_time = time.time()

print("\nリアルタイムEMG解析＋波形描画開始 (Ctrl+Cで終了)\n")

try:
    while True:
        current_time = time.time()
        dt = current_time - prev_time
        prev_time = current_time
        data_rate = 1.0 / dt if dt > 0 else 0.0

        # ==== 最新フレーム取得 ====
        frame_full = cam.get_latest_frame()
        if frame_full is None:
            print("\r⚠ キャプチャ失敗（ウィンドウが非表示？）", end="")
            continue

        # ==== 色変換（dxcamはBGR出力） ====
        frame_full = cv2.cvtColor(frame_full, cv2.COLOR_BGR2RGB)

        # ==== 対象ウィンドウの位置からROI切り出し ====
        try:
            wx1, wy1, wx2, wy2 = win32gui.GetWindowRect(hwnd)
            roi = frame_full[wy1 + y_min:wy1 + y_max, wx1 + x_min:wx1 + x_max]
        except Exception as e:
            print(f"\rROI切り出し失敗: {e}", end="")
            continue

        if roi.size == 0:
            continue

        img = cv2.cvtColor(roi, cv2.COLOR_RGB2GRAY)
        _, img_otsu = cv2.threshold(img, 0, 255, cv2.THRESH_OTSU)

        # ==== 差分 ====
        if prev_frame is not None:
            diff = cv2.absdiff(img_otsu, prev_frame)
            diff_binary = cv2.threshold(diff, 50, 255, cv2.THRESH_BINARY)[1]
        else:
            diff_binary = np.zeros_like(img_otsu)
        prev_frame = img_otsu.copy()

        ys_diff, xs_diff = np.where(diff_binary == 255)
        if len(xs_diff) > 0:
            x_min_line = np.min(xs_diff)
            x_max_line = np.max(xs_diff) - 1

            if x_max_line - x_min_line < x_range_max:
                mask_x = np.zeros_like(img_otsu, dtype=bool)
                mask_x[:, x_min_line:x_max_line + 1] = True
                ys_line, xs_line = np.where((img_otsu > 127) & mask_x)

                if len(ys_line) > 0:
                    y_mean = np.mean(ys_line)
                    emg_val = max_voltage * (1 - (y_mean / origin))
                else:
                    emg_val = 0.0
        else:
            emg_val = 0.0

        emg_values.append(emg_val)

        top_edge = np.mean(img_otsu[0, :])
        bottom_edge = np.mean(img_otsu[-1, :])
        left_edge = np.mean(img_otsu[:, 0])
        right_edge = np.mean(img_otsu[:, -1])
        edge_status = lambda val: "白" if val > 127 else "黒"

        print(
            f"\rEMG: {emg_val:+.3f} V | 上:{edge_status(top_edge)}({top_edge:.1f}) "
            f"下:{edge_status(bottom_edge)}({bottom_edge:.1f}) "
            f"左:{edge_status(left_edge)}({left_edge:.1f}) "
            f"右:{edge_status(right_edge)}({right_edge:.1f}) "
            f"| データレート: {data_rate:.1f} Hz ",
            end=""
        )

        vis = cv2.cvtColor(img_otsu, cv2.COLOR_GRAY2BGR)
        diff_vis = cv2.cvtColor(diff_binary, cv2.COLOR_GRAY2BGR)
        combined = np.hstack((vis, diff_vis))
        cv2.imshow("EMG Live | 差分表示", combined)

        line.set_ydata(emg_values)
        plt.pause(0.001)

        if cv2.waitKey(1) & 0xFF == 27:
            break

        time.sleep(0.01)

except KeyboardInterrupt:
    print("\n終了しました。")

finally:
    cam.stop()
    cv2.destroyAllWindows()
    plt.ioff()
    plt.show()
