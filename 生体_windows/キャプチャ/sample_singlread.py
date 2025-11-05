import cv2
import numpy as np
from PIL import ImageGrab
import time
import win32gui
import win32con

# ==== 対象ウィンドウのタイトル ====
TARGET_TITLE = "EmotivPRO 4.8.10.593"

# ==== キャプチャ範囲 ====
x_min, y_min, x_max, y_max = 2900, 79, 2966, 521
origin = y_max - y_min
max_voltage = 200.0       # スケーリング上限
y_center = origin / 2     # 0V基準位置（中央）

# ==== 読み取り列を指定 ====
read_col = x_max - 1  # 右端の列

# ==== 対象ウィンドウを取得 ====
hwnd = win32gui.FindWindow(None, TARGET_TITLE)
if hwnd == 0:
    raise Exception(f"ウィンドウ '{TARGET_TITLE}' が見つかりません。")

# ==== ウィンドウを左上に移動 ====
win32gui.SetWindowPos(hwnd, win32con.HWND_TOP, 0, 0, 3072, 1920, 0)
print(f"ウィンドウ '{TARGET_TITLE}' を画面左上に移動しました。")

# ==== EMG解析開始 ====
print("\n指定列のグラフ解析開始 (Ctrl+Cで終了)\n")

try:
    last_time = time.time()
    frame_count = 0

    while True:
        # ==== キャプチャ ====
        img = np.array(ImageGrab.grab(bbox=(x_min, y_min, x_max, y_max)))
        gray = cv2.cvtColor(img, cv2.COLOR_RGB2GRAY)

        # ==== 黒線検出のため反転 ====
        img_inv = cv2.bitwise_not(gray)

        # ==== 二値化 ====
        _, img_bin = cv2.threshold(img_inv, 180, 255, cv2.THRESH_BINARY)

        # ==== 指定列のピクセル抽出 ====
        col_pixels = img_bin[:, read_col - x_min]
        ys = np.where(col_pixels == 255)[0]

        # ==== EMG値算出 ====
        if len(ys) > 0:
            y_mean = np.mean(ys)
            emg_val = -max_voltage * ((y_mean - y_center) / y_center)
        else:
            y_mean = -1
            emg_val = 0.0

        # ==== FPS計算 ====
        frame_count += 1
        now = time.time()
        elapsed = now - last_time
        if elapsed >= 1.0:
            fps = frame_count / elapsed
            frame_count = 0
            last_time = now
        else:
            fps = None

        msg = f"\r列={read_col} | y_mean={y_mean:6.1f} | EMG={emg_val:+7.2f} μV"
        if fps:
            msg += f" | FPS={fps:4.1f}"
        print(msg, end="")

        # ==== 可視化 ====
        # 元画像（カラー）
        img_bgr = cv2.cvtColor(img, cv2.COLOR_RGB2BGR)

        # 二値化画像にラインを描画
        vis = cv2.cvtColor(img_bin, cv2.COLOR_GRAY2BGR)
        cv2.line(vis, (read_col - x_min, 0), (read_col - x_min, vis.shape[0]), (0, 0, 255), 1)  # 読み取り列（赤）
        cv2.line(vis, (0, int(y_center)), (vis.shape[1], int(y_center)), (255, 0, 0), 1)        # 0V基準線（青）

        # 2つを横並びで表示
        combined = np.hstack((img_bgr, vis))
        cv2.imshow("EMG Capture (左=原画像 / 右=検出結果)", combined)

        if cv2.waitKey(1) & 0xFF == 27:  # ESCで終了
            break

        time.sleep(0.01)

except KeyboardInterrupt:
    print("\n終了しました。")
finally:
    cv2.destroyAllWindows()
