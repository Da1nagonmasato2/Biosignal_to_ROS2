#  Biosignal_to_ROS2

Windows側で取得した生体信号（筋電・脳波） を  
Linux（ROS2）側へ送信するためのプロジェクトです。

---

##  Windows 側セットアップ

### 1. リポジトリの取得

以下のいずれかで取得します。

#### 🔹 特定フォルダのみ取得（軽量）

```bash
git clone --no-checkout https://github.com/Da1nagonmasato2/Biosignal_to_ROS2.git
cd Biosignal_to_ROS2
git sparse-checkout init --cone
git sparse-checkout set windows
```

#### 🔹 またはリポジトリ全体をクローン
```bash
git clone https://github.com/Da1nagonmasato2/Biosignal_to_ROS2.git
```

---

### 2. Pythonライブラリのインストール

```bash
pip install --upgrade pip
pip install dxcam
```

---

### 3. 使用するソフトウェア

#### 筋電（EMG）

- 使用ソフト：  
  追坂電子工業製「ワイヤレス筋電_アクセサリパック ver7.8.01」

- インストール方法：  
  CD-ROM または 実験室PCのデスクトップから  
  `ワイヤレス筋電_アクセサリパックver7.8.01\LabVIEW_Application\installer\setup`  
  を実行して LabVIEW 環境をセットアップ。


現在研究室にはこのアプリを使う筋電センサが二つあるが表面につやがある筋電センサは使用
有線接続では電源供給由来のノイズが入る。
詳細な使い方はNotion を参照。

---

#### 脳波（EEG）

- 使用ソフト：  
  Emotiv 社製「EmotivPRO」  
  https://www.emotiv.com/products/emotivpro  
  上記サイトからダウンロード（アカウント登録等が必要）  
  詳細は Notion を参照。

---

## Linux (ROS2) 側セットアップ

### 1. LSLワークスペースを準備

```bash
git clone --no-checkout https://github.com/Da1nagonmasato2/Biosignal_to_ROS2.git
cd Biosignal_to_ROS2
git sparse-checkout init --cone
git sparse-checkout set linux
```

または：

```bash
git clone https://github.com/Da1nagonmasato2/Biosignal_to_ROS2.git
```

---

### 2. LSL ライブラリのビルド

```bash
git clone https://github.com/sccn/labstreaminglayer
cd labstreaminglayer
git submodule update --init --recursive
cmake .. --DCMAKE_BUILD_TYPE=Release
cmake --build . --config Release
sudo cmake --build . --config Release --target install
```

---

### 3. ROS2 ワークスペースをビルド

```bash
cd ~/lsl_ws
colcon build
```

---

## 計測方法

### 共通設定

- Windowsの設定 → 「ディスプレイ」→「拡大/縮小」を 100% に設定。
- 画面解像度を1900x1200に変更
- 画面キャプチャを使用するため、グラフ上に他のウィンドウを重ねないこと。

---

### 筋電（EMG）を ROS2 に送信する

#### Windows側

1. `ワイヤレス筋電_アクセサリパックver7.8.01\LabVIEW_Application\exe\data\appSetting`  
   内の `Chart03Max`, `Chart03Min` を測定したいレンジ（単位：V）に設定。

2. `lp_wSensor7_std.exe` を起動し、計測を開始してレンジが反映されていることを確認。

3. `windows/生体_windows/データ送信/使用するプログラム` 内の  
   - `max_voltage` を上記レンジ値に合わせる。  
   - `TARGET_TITLE` がアプリウィンドウ名と一致しているか確認。

4. 送信方式
   - `EMG_mean`: キャプチャ領域の平均値を送信  
   - `EMG_peak`: 最大値を送信  

5. 実行：
   ```bash
   python 使用するプログラム名.py
   ```
   データレート（送信頻度）が表示されれば成功。

---

### 脳波（EEG）を ROS2 に送信する

#### Windows側

1. EmotivPRO を起動し、EEGデバイスと接続。

2. 波形表示画面で：
   - `Channel Spacing` を測定したいレンジに合わせる。  
   - 目のアイコンから測定チャネルを`Cz`, `C3`, `O1`, `O2`に設定。

3. `windows/生体_windows/データ送信/使用するプログラム` 内の  
   - `max_voltage` を測定したいレンジ値に合わせる。  
   - `TARGET_TITLE` をウィンドウ名に合わせる。

4. 送信方式
   - `EEG_mean`: 平均値送信  
   - `EEG_peak`: 最大値送信  

5. 実行：
   ```bash
   python 使用するプログラム名.py
   ```
   データレートが表示されればOK。

---


