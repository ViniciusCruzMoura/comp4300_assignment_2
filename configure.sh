apt -y update
apt -y install build-essential gcc git cmake
apt -y install libasound2-dev libx11-dev libxrandr-dev libxi-dev libgl1-mesa-dev libglu1-mesa-dev libxcursor-dev libxinerama-dev libwayland-dev libxkbcommon-dev
git clone --depth 1 https://github.com/raysan5/raylib.git raylib
cd raylib/src/
make 
make install
cd ../../
rm -rf raylib/
