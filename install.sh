#!/bin/bash

#Compilación
if [ -d "build" ]; then
    sudo rm -rf "build"
fi
mkdir build
cd build
cmake ..
cmake --build .
sudo make install
#Correr los tests unitarios
cd tests
./taller_tests