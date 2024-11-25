#!/bin/bash

#Instalación de dependencias necesarias
#C++
sudo apt -y install build-essential
sudo apt -y install cmake
#SDL2
sudo apt -y install libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev libsdl2-ttf-dev libjpeg-dev libpng-dev libfreetype-dev libopusfile-dev libflac-dev libxmp-dev libfluidsynth-dev libwavpack-dev cmake libmodplug-dev

#QT
sudo apt -y install qtcreator qtbase5-dev qtchooser qt5-qmake qtbase5-dev-tools
sudo apt -y install libqt5charts5-dev libqt5datavisualization5-dev libqt5gamepad5-dev libqt5gstreamer-dev libqt5networkauth5-dev libqt5opengl5-dev libqt5remoteobjects5-dev libqt5scxml5-dev libqt5sensors5-dev libqt5serialbus5-dev libqt5serialport5-dev libqt5svg5-dev libqt5texttospeech5-dev libqt5virtualkeyboard5-dev libqt5waylandclient5-dev libqt5waylandcompositor5-dev libqt5webkit5-dev libqt5webchannel5-dev libqt5websockets5-dev libqt5webview5-dev libqt5x11extras5-dev libqt5xmlpatterns5-dev
#YAML
sudo apt-get -y install libyaml-cpp-dev
#TESTS
sudo apt-get -y install libgtest-dev