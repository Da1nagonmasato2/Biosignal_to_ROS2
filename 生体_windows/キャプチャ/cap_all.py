# capture_once.py
from PIL import ImageGrab
import os

# 保存先ディレクトリ
save_dir = "captures"
os.makedirs(save_dir, exist_ok=True)

# ファイル名
file_name = os.path.join(save_dir, "screenshot.bmp")

# 全画面キャプチャ
img = ImageGrab.grab()

# 保存
img.save(file_name)

print(f"スクリーンショットを保存しました: {file_name}")
