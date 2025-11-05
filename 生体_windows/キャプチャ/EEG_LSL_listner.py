from pylsl import StreamInlet, resolve_stream
import numpy as np
import matplotlib.pyplot as plt
from collections import deque
import time

# ==== 受信設定 ====
STREAM_NAME = "EEG_stream"
BUFFER_SIZE = 500  # グラフ上のサンプル数（大きいほど長時間表示）

print(f"LSLストリーム '{STREAM_NAME}' を検索中...")
streams = resolve_stream('name', STREAM_NAME)
if not streams:
    raise RuntimeError(f"LSLストリーム '{STREAM_NAME}' が見つかりません。送信側が動作中か確認してください。")

inlet = StreamInlet(streams[0])
info = inlet.info()
n_channels = info.channel_count()
channel_labels = info.desc().child("channels").child_value("labels").split(",") if info.desc().child("channels").child_value("labels") else [f"CH{i}" for i in range(n_channels)]
print(f"受信ストリーム情報: {n_channels}ch ({channel_labels})")

# ==== グラフ初期化 ====
plt.ion()
fig, ax = plt.subplots(figsize=(10, 6))
lines = []
buffers = [deque([0.0]*BUFFER_SIZE, maxlen=BUFFER_SIZE) for _ in range(n_channels)]
x = np.arange(BUFFER_SIZE)

for i in range(n_channels):
    line, = ax.plot(x, buffers[i], label=channel_labels[i])
    lines.append(line)

ax.set_ylim(-250, 250)  # μV単位
ax.set_xlabel("Time (frames)")
ax.set_ylabel("EMG (μV)")
ax.set_title("EMG Real-time Waveform (LSL受信)")
ax.legend(loc="upper right")
plt.tight_layout()

print("リアルタイム受信開始 (Ctrl+Cで終了)\n")

try:
    while True:
        sample, timestamp = inlet.pull_sample(timeout=1.0)
        if sample is None:
            print("⚠ データ受信が停止中")
            time.sleep(0.1)
            continue

        # ==== 各チャンネル値をバッファに格納 ====
        for i in range(n_channels):
            buffers[i].append(sample[i])

        # ==== グラフ更新 ====
        for i in range(n_channels):
            lines[i].set_ydata(buffers[i])

        plt.pause(0.01)

except KeyboardInterrupt:
    print("\n終了しました。")
finally:
    plt.ioff()
    plt.show()
