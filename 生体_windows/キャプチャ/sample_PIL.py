# realtime_emg_dxcam_plot_white.py
import dxcam
import cv2
import numpy as np
import time
import win32gui
import win32con
import matplotlib.pyplot as plt
from collections import deque

# ==== 対象ウィンドウのタイトル ====
TARGET_TITLE = "ロジカルプロダクト ワイヤレスセンサモジュール Ver7.8.01_LP"

# ==== キャプチャ範囲（ウィンドウ移動後のROI）====
x_min, y_min, x_max, y_max = 92, 190, 726, 266
origin = 78
max_voltage = 0.05
x_range_max=50

# ==== グラフ設定 ====
MAX_POINTS = 300  # 表示するデータ点数
emg_values = deque([0.0] * MAX_POINTS, maxlen=MAX_POINTS)

# ==== 対象ウィンドウを取得 ====
hwnd = win32gui.FindWindow(None, TARGET_TITLE)
if hwnd == 0:
    raise Exception(f"ウィンドウ '{TARGET_TITLE}' が見つかりません。")

# ==== ウィンドウを左上に移動 ====
win32gui.SetWindowPos(hwnd, win32con.HWND_TOP, 0, 0, 800, 600, 0)
print(f"ウィンドウ '{TARGET_TITLE}' を画面左上に移動しました。")

# ==== DXCAM カメラ作成 (GPUなし) ====
cam = dxcam.create()

print("\nリアルタイムEMG解析＋波形描画開始 (Ctrl+Cで終了)\n")

# ==== グラフ準備 ====
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

try:
    while True:
        current_time = time.time()
        dt = current_time - prev_time
        prev_time = current_time
        data_rate = 1.0 / dt if dt > 0 else 0.0

        # ---- 画像キャプチャ ----
        frame = cam.grab(region=(x_min, y_min, x_max, y_max))
        if frame is None:
            print("\r⚠ キャプチャ失敗（ウィンドウが非表示？）", end="")
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

       
        # ---- 差分のある x 座標を検出 ----
        ys_diff, xs_diff = np.where(diff_binary == 255)
        if len(xs_diff) > 0:
         x_min_line = np.min(xs_diff)
         #更新戦を値として読まないようにする
         x_max_line = np.max(xs_diff)-1

         if x_max_line-x_min_line < x_range_max:
              
               # 元画像から差分 x 範囲の白線の y 座標を取得
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

        # ---- 各ふちの平均輝度 ----
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

        # ---- 可視化 ----
        vis = cv2.cvtColor(img_otsu, cv2.COLOR_GRAY2BGR)
        diff_vis = cv2.cvtColor(diff_binary, cv2.COLOR_GRAY2BGR)
        combined = np.hstack((vis, diff_vis))
        cv2.imshow("EMG Live | 差分表示", combined)

        # ---- グラフ更新 ----
        line.set_ydata(emg_values)
        plt.pause(0.001)

        if cv2.waitKey(1) & 0xFF == 27:  # ESCで終了
            break

        time.sleep(0.01)

except KeyboardInterrupt:
    print("\n終了しました。")
finally:
    cv2.destroyAllWindows()
    plt.ioff()
    plt.show()
