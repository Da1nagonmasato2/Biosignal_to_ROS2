Linux(ROS2側)の設定
lsl_wsをクローンする。
git clone --no-checkout https://github.com/Da1nagonmasato2/Biosignal_to_ROS2.git
cd Biosignal_to_ROS2
git sparse-checkout init --cone
git sparse-checkout set windows
別にリポジトリ全体をクローンしてもいい

必要なライブラリを準備する
git clone https://github.com/sccn/labstreaminglayer
cd labstreaminglayer
必要なライブラリをインストールする
必要なサブモジュールをインストールする
git submodule update --init --recursive
ライブラリをビルドしてインストール
cmake ..　--DCMAKE_BUILD_TYPE=Release
cmake --build . --config Rerease
sudo cmake --build . --config Rerease --target install

lsl_ws直下でビルドをする
colcon build
