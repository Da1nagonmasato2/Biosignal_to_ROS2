import cv2
import numpy as np
import time
import win32gui
import win32con
import dxcam

# ==== 対象ウィンドウのタイトル ====
TARGET_TITLE = "EmotivPRO 4.8.10.593"

# ==== グラフ設定 ====
# 縦に4つ並んでいると仮定
graph_height = 213
x_min, x_max = 1790, 1800
y_offsets = [111, 111 + 242, 111 + 242*2, 111 + 242*3]  # A, B, C, D
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
win32gui.SetWindowPos(hwnd, win32con.HWND_TOP, 0, 0, 1920, 1200, 0)
print(f"ウィンドウ '{TARGET_TITLE}' を画面左上に移動しました。")

# ==== dxcam初期化 ====
try:
    cam = dxcam.create(output_color="RGB")
    print("dxcam: GPUモードでキャプチャ開始")
except Exception:
    print("dxcam: GPUが使用できないためCPUモードに切替")
    cam = dxcam.create(output_color="RGB", device_idx=0)

print("\nEMGグラフ (A, B, C, D) の解析開始 (Ctrl+Cで終了)\n")

try:
    last_time = time.time()
    frame_count = 0

    while True:
        # ==== 一括キャプチャ ====
        frame_full = cam.grab(region=(x_min, y_min_all, x_max, y_max_all))
        if frame_full is None:
            print("\n⚠ キャプチャ失敗（ウィンドウが非表示？）")
            time.sleep(0.1)
            continue

        # ==== グレースケール変換 ====
        gray_full = cv2.cvtColor(frame_full, cv2.COLOR_RGB2GRAY)

        results = []
        vis_rows = []

        # ==== 各ROIで個別二値化・解析 ====
        for ch_name, y_min_local in zip(channels, y_offsets):
            y0 = y_min_local - y_min_all
            y1 = y0 + graph_height
            y_center = graph_height / 2

            # 個別ROI抽出
            roi_gray = gray_full[y0:y1, :]
            roi_inv = cv2.bitwise_not(roi_gray)

            # --- 個別に二値化（Otsu法で自動しきい値）---
            _, roi_bin = cv2.threshold(roi_inv, 0, 255, cv2.THRESH_BINARY + cv2.THRESH_OTSU)

            # 指定列のピクセル抽出
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

            # 可視化用
            vis = cv2.cvtColor(roi_bin, cv2.COLOR_GRAY2BGR)
            cv2.line(vis, (read_col, 0), (read_col, vis.shape[0]), (0, 0, 255), 1)
            cv2.line(vis, (0, int(y_center)), (vis.shape[1], int(y_center)), (255, 0, 0), 1)
            cv2.putText(vis, f"CH {ch_name}", (5, 20),
                        cv2.FONT_HERSHEY_SIMPLEX, 0.6, (0, 255, 0), 1)
            vis_rows.append(np.hstack((cv2.cvtColor(roi_gray, cv2.COLOR_GRAY2BGR), vis)))

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

        # ==== 結果出力 ====
        msg = "\r" + " ".join(
            [f"{ch}: y_mean={y_mean:6.1f} EMG={emg:+7.2f}μV" for ch, y_mean, emg in results]
        )
        if fps:
            msg += f" | FPS={fps:4.1f}"
        print(msg, end="")

        # ==== 可視化 ====
        combined = np.vstack(vis_rows)
        cv2.imshow("EMG Capture (左=原画像 / 右=検出結果)", combined)

        if cv2.waitKey(1) & 0xFF == 27:
            break

        time.sleep(0.01)

except KeyboardInterrupt:
    print("\n終了しました。")
finally:
    cv2.destroyAllWindows()
    cam.stop()
