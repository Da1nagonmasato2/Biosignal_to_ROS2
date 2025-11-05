import pyautogui
import time

print("マウスを動かしてください。Ctrl+Cで終了します。\n")

try:
    while True:
        x, y = pyautogui.position()
        print(f"X: {x:3d}")  # 3桁固定
        print(f"Y: {y:3d}")  # 3桁固定
        time.sleep(0.1)
        print("\033[F\033[F", end="")  # 上2行にカーソルを戻す
except KeyboardInterrupt:
    print("\n終了しました。")
