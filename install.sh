#!/bin/bash

#Compilación
if [ -d "build" ]; then
    rm -rf "build"
fi
mkdir build
cd build
cmake ..
cmake --build .

#Correr los tests unitarios
./taller_tests

#Mover archivos
if [ -f "/usr/bin/taller_client" ]; then
    sudo rm -f "/usr/bin/taller_client"
fi

if [ -f "/usr/bin/taller_server" ]; then
    sudo rm -f "/usr/bin/taller_server"
fi

if [ -f "/usr/bin/taller_editor" ]; then
    sudo rm -f "/usr/bin/taller_editor"
fi

sudo cp -p -f taller_client taller_server taller_editor /usr/bin
cd ..
if [ -d "/etc/TallerDuckGame" ]; then
    sudo rm -rf "/etc/TallerDuckGame"
fi
sudo mkdir /etc/TallerDuckGame 
sudo cp -p -f  data/editor/menu_config.yaml server/configuration/config.yaml /etc/TallerDuckGame
if [ -d "/var/TallerDuckGame" ]; then
    sudo rm -rf "/var/TallerDuckGame"
fi
sudo mkdir /var/TallerDuckGame 
sudo cp -p -f -r data /var/TallerDuckGame
