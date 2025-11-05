from pylsl import StreamInlet, resolve_stream
import matplotlib.pyplot as plt
from collections import deque
import time

# ==== LSLストリーム探索 ====
print("EMGストリームを探索中...")
streams = resolve_stream('name', 'EMG_Stream')  # 送信側のストリーム名と一致
inlet = StreamInlet(streams[0])
print("EMGストリーム受信開始")

# ==== 波形描画準備 ====
MAX_POINTS = 300
emg_values = deque([0.0]*MAX_POINTS, maxlen=MAX_POINTS)

plt.ion()
fig, ax = plt.subplots(figsize=(8,3))
(line,) = ax.plot(emg_values, color="lime")
ax.set_ylim(-0.06, 0.06)  # max_voltageに合わせる
ax.set_xlim(0, MAX_POINTS)
ax.set_xlabel("Time (frames)")
ax.set_ylabel("EMG Voltage (V)")
ax.grid(True)

try:
    while plt.fignum_exists(fig.number):  # ウィンドウが閉じられたら終了
        sample, timestamp = inlet.pull_sample(timeout=0.1)
        if sample is not None:
            emg_val = sample[0]
        else:
            emg_val = 0.0

        # 波形更新
        emg_values.append(emg_val)
        line.set_ydata(emg_values)
        plt.pause(0.001)

        # 値を表示
        print(f"\rタイムスタンプ {timestamp:.3f} s : EMG = {emg_val:+.3f} V", end="")

except KeyboardInterrupt:
    print("\n受信終了")

finally:
    plt.ioff()
    plt.show()
