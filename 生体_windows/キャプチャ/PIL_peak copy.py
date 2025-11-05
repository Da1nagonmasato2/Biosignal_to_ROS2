import dxcam
import numpy as np
import cv2
import time
import matplotlib.pyplot as plt
from collections import deque

# ==== キャプチャ範囲（スクリーン座標）====
x_min, y_min, x_max, y_max = 92, 190, 726, 266
origin = 78
max_voltage = 0.05
x_range_max = 50

# ==== グラフ設定 ====
MAX_POINTS = 300
emg_values = deque([0.0] * MAX_POINTS, maxlen=MAX_POINTS)

plt.ion()
fig, ax = plt.subplots(figsize=(8, 3))
(line,) = ax.plot(emg_values, color="lime")
ax.set_ylim(-max_voltage * 1.1, max_voltage * 1.1)
ax.set_xlim(0, MAX_POINTS)
ax.set_xlabel("Time (frames)")
ax.set_ylabel("EMG Voltage (V)")
ax.grid(True)

# ==== dxcam 初期化 ====
camera = dxcam.create(output_color="RGB")  # RGBで取得
roi = (x_min, y_min, x_max, y_max)
camera.start(region=roi, target_fps=30)  # 非同期キャプチャ開始

prev_frame = None
prev_time = time.time()

print("\nリアルタイムEMG解析＋波形描画開始 (Ctrl+Cで終了)\n")

try:
    while True:
        current_time = time.time()
        dt = current_time - prev_time
        prev_time = current_time
        data_rate = 1.0 / dt if dt > 0 else 0.0

        # ==== dxcamで画面キャプチャ ====
        frame = camera.get_latest_frame()
        if frame is None:
            time.sleep(0.001)
            continue

        img = cv2.cvtColor(frame, cv2.COLOR_RGB2GRAY)
        _, img_otsu = cv2.threshold(img, 0, 255, cv2.THRESH_OTSU)

        # ---- 差分計算 ----
        if prev_frame is not None:
            diff = cv2.absdiff(img_otsu, prev_frame)
            diff_binary = cv2.threshold(diff, 50, 255, cv2.THRESH_BINARY)[1]
        else:
            diff_binary = np.zeros_like(img_otsu)
        prev_frame = img_otsu.copy()

        # ---- 差分から白線範囲検出 ----
        ys_diff, xs_diff = np.where(diff_binary == 255)
        if len(xs_diff) > 0:
            x_min_line = np.min(xs_diff)
            x_max_line = np.max(xs_diff) - 1

            if x_max_line - x_min_line < x_range_max:
                mask_x = np.zeros_like(img_otsu, dtype=bool)
                mask_x[:, x_min_line:x_max_line + 1] = True

                # ==== ピーク値（最上端）を取得 ====
                try:
                    y_peak = np.min(np.nonzero((img_otsu > 127) & mask_x)[0])
                    emg_val = max_voltage * (1 - (y_peak / origin))
                except ValueError:
                    emg_val = 0.0
        else:
            emg_val = 0.0

        emg_values.append(emg_val)

        # ---- デバッグ出力 ----
        print(f"\rEMG: {emg_val:+.3f} V | データレート: {data_rate:.1f} Hz ", end="")

        # ---- 可視化 ----
        vis = cv2.cvtColor(img_otsu, cv2.COLOR_GRAY2BGR)
        diff_vis = cv2.cvtColor(diff_binary, cv2.COLOR_GRAY2BGR)
        combined = np.hstack((vis, diff_vis))
        cv2.imshow("EMG Live | 差分表示", combined)

        # ---- グラフ更新 ----
        line.set_ydata(emg_values)
        plt.pause(0.001)

        if cv2.waitKey(1) & 0xFF == 27:
            break

        time.sleep(0.01)  # 軽いウェイトでCPU負荷軽減

except KeyboardInterrupt:
    print("\n終了しました。")

finally:
    camera.stop()
    cv2.destroyAllWindows()
    plt.ioff()
    plt.show()
