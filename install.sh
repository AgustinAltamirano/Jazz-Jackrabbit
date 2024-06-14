# shellcheck disable=SC2028
echo "Instalador de dependencias del proyecto\n"

git submodule update --init --recursive

# Librerías principales del proyecto
sudo apt install cmake \
  make \
  clang \
  build-essential \
  libyaml-cpp-dev \
  qtbase5-dev \
  qtmultimedia5-dev \
  libsdl2-dev -y

# Librerías necesarias para SDL
sudo apt install libopusfile-dev \
  libxmp-dev \
  libfluidsynth-dev \
  libwavpack-dev \
  libfreetype-dev \
  libjpeg-dev \
  libpng-dev -y

EXTLIB="extlib"

cd $EXTLIB || exit
wget "https://github.com/libsdl-org/SDL_image/releases/download/release-2.8.2/SDL2_image-2.8.2.zip" -P "."
wget "https://github.com/libsdl-org/SDL_mixer/releases/download/release-2.8.0/SDL2_mixer-2.8.0.zip" -P "."
wget "https://github.com/libsdl-org/SDL_ttf/releases/download/release-2.22.0/SDL2_ttf-2.22.0.zip" -P "."

unzip "SDL2_image-2.8.2.zip" -d "."
unzip "SDL2_mixer-2.8.0.zip" -d "."
unzip "SDL2_ttf-2.22.0.zip" -d "."


cd "SDL2_image-2.8.2" || exit
mkdir -p build
cd build || exit
cmake ..
make -j4
sudo make install

cd ../.. || exit
cd "SDL2_mixer-2.8.0" || exit
mkdir -p build
cd build || exit
cmake ..
make -j4
sudo make install

cd ../.. || exit
cd "SDL2_ttf-2.22.0" || exit
mkdir -p build
cd build || exit
cmake ..
make -j4
sudo make install

cd ../.. || exit
cd "libSDL2pp" || exit
mkdir -p build
cd build || exit
cmake ..
make -j4
sudo make install

cd ../../..

sudo sh build.sh