#!/bin/bash

#Instalación de dependencias necesarias
#C++
sudo apt install build-essential
sudo apt install cmake
#SDL2
sudo apt install libsdl2-dev
sudo apt install libsdl2-image-dev libsdl2-mixer-dev libsdl2-ttf-dev
sudo apt install libjpeg-dev libpng-dev libfreetype-dev libopusfile-dev libflac-dev libxmp-dev libfluidsynth-dev libwavpack-dev cmake libmodplug-dev libsdl2-dev
mkdir sdl2
cd sdl2
wget https://github.com/libsdl-org/SDL_ttf/releases/download/release-2.22.0/SDL2_ttf-2.22.0.zip
wget https://github.com/libsdl-org/SDL_mixer/releases/download/release-2.8.0/SDL2_mixer-2.8.0.zip
wget https://github.com/libsdl-org/SDL_image/releases/download/release-2.8.2/SDL2_image-2.8.2.zip
wget https://github.com/libSDL2pp/libSDL2pp/archive/refs/tags/0.18.1.zip
unzip SDL2_ttf-2.22.0.zip
unzip SDL2_mixer-2.8.0.zip
unzip SDL2_image-2.8.2.zip 
unzip libSDL2pp-0.18.1.zip
cd SDL_image-release-2.8.2
mkdir build
cd build
cmake ..
make -j4
sudo make install
cd ..
cd SDL_mixer-release-2.8.0
mkdir build
cd build
cmake ..
make -j4
sudo make install
cd ..
cd SDL_ttf-release-2.22.0
mkdir build
cd build
cmake ..
make -j4
sudo make install
cd ..
cd libSDL2pp-0.18.1
mkdir build
cd build
cmake ..
make -j4
sudo make install
cd ../../
#QT
sudo apt install qtcreator qtbase5-dev qtchooser qt5-qmake qtbase5-dev-tools
sudo apt install libqt5charts5-dev libqt5datavisualization5-dev libqt5gamepad5-dev libqt5gstreamer-dev libqt5networkauth5-dev libqt5opengl5-dev libqt5remoteobjects5-dev libqt5scxml5-dev libqt5sensors5-dev libqt5serialbus5-dev libqt5serialport5-dev libqt5svg5-dev libqt5texttospeech5-dev libqt5virtualkeyboard5-dev libqt5waylandclient5-dev libqt5waylandcompositor5-dev libqt5webkit5-dev libqt5webchannel5-dev libqt5websockets5-dev libqt5webview5-dev libqt5x11extras5-dev libqt5xmlpatterns5-dev
#YAML
sudo apt-get install libyaml-cpp-dev