import win32gui
import win32con
import ctypes

# ウィンドウタイトル
window_title = "Microsoft Store"

# ウィンドウハンドル取得
hwnd = win32gui.FindWindow(None, window_title)
if hwnd == 0:
    raise Exception("ウィンドウが見つかりません")

# 最小化や最大化を解除
win32gui.ShowWindow(hwnd, win32con.SW_RESTORE)

# 画面サイズ取得（物理ピクセル）
user32 = ctypes.windll.user32
screen_width = user32.GetSystemMetrics(0)   # 横幅
screen_height = user32.GetSystemMetrics(1)  # 高さ

# 左半分のサイズ
x = 0
y = 0
width = screen_width // 2
height = screen_height

# ウィンドウ移動・リサイズ
win32gui.MoveWindow(hwnd, x, y, width, height, True)

print(f"{window_title} を画面左半分に移動しました")
