import os
import win32gui
import win32ui
import win32con
import win32api

# 設定
window_title = "EMOTIV Launcher 4.8.10.417"
save_dir = "captures"
os.makedirs(save_dir, exist_ok=True)
file_path = os.path.join(save_dir, "window_capture.bmp")

# DPI補正を行う関数
def get_scale(hwnd):
    try:
        # Windows 10 以降なら取得可能
        from ctypes import windll
        dpi = windll.user32.GetDpiForWindow(hwnd)
        scale = dpi / 96.0  # 標準96dpi基準
        return scale
    except Exception:
        return 1.0  # 古い環境では1.0固定

# ウィンドウハンドル取得
hwnd = win32gui.FindWindow(None, window_title)
if hwnd == 0:
    raise Exception("指定したウィンドウが見つかりません。")

# DPIスケーリング取得
scale = get_scale(hwnd)
print(f"DPIスケール: {scale}")

# ウィンドウの座標取得（物理ピクセル換算）
left, top, right, bottom = win32gui.GetWindowRect(hwnd)
left = int(left * scale)
top = int(top * scale)
right = int(right * scale)
bottom = int(bottom * scale)
width = right - left
height = bottom - top

# デバイスコンテキスト
hwndDC = win32gui.GetWindowDC(hwnd)
mfcDC = win32ui.CreateDCFromHandle(hwndDC)
saveDC = mfcDC.CreateCompatibleDC()

# 互換ビットマップ
saveBitMap = win32ui.CreateBitmap()
saveBitMap.CreateCompatibleBitmap(mfcDC, width, height)
saveDC.SelectObject(saveBitMap)

# BitBlt転送
saveDC.BitBlt((0, 0), (width, height), mfcDC, (0, 0), win32con.SRCCOPY)

# 保存
saveBitMap.SaveBitmapFile(saveDC, file_path)

# 解放
win32gui.DeleteObject(saveBitMap.GetHandle())
saveDC.DeleteDC()
mfcDC.DeleteDC()
win32gui.ReleaseDC(hwnd, hwndDC)

print(f"ウィンドウキャプチャを保存しました: {file_path}")
