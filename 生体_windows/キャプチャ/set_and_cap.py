# -*- coding: utf-8 -*-
import os
import win32gui
import win32con
import ctypes
from PIL import ImageGrab
import time

# -------------------------------
# 設定
# -------------------------------
window_title = "Microsoft Store"  # キャプチャ対象
save_dir = "captures"                                     # 保存先ディレクトリ
file_name = "window_left_half_capture.bmp"               # 保存ファイル名

os.makedirs(save_dir, exist_ok=True)
file_path = os.path.join(save_dir, file_name)

# -------------------------------
# ウィンドウ取得
# -------------------------------
hwnd = win32gui.FindWindow(None, window_title)
if hwnd == 0:
    raise Exception("指定したウィンドウが見つかりません。")

# 最小化や最大化を解除
win32gui.ShowWindow(hwnd, win32con.SW_RESTORE)
time.sleep(0.5)  # ウィンドウが安定するまで少し待つ

# -------------------------------
# 画面左半分に移動
# -------------------------------
user32 = ctypes.windll.user32
screen_width = user32.GetSystemMetrics(0)
screen_height = user32.GetSystemMetrics(1)

x = 0
y = 0
width = screen_width // 2
height = screen_height

win32gui.MoveWindow(hwnd, x, y, width, height, True)
time.sleep(0.5)  # 移動後に再描画されるのを待つ

# -------------------------------
# ウィンドウ座標取得
# -------------------------------
# 枠込み座標
left, top, right, bottom = win32gui.GetWindowRect(hwnd)

# -------------------------------
# 全画面キャプチャ + 切り抜き
# -------------------------------
full_img = ImageGrab.grab()
img = full_img.crop((left, top, right*2, bottom*2))
img.save(file_path)

print(f"ウィンドウキャプチャを保存しました: {file_path}")
