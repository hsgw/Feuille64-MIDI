#!/bin/sh

echo "Flash with dfu-programmer on wsl2"
"/mnt/c/Program Files/dfu-programmer/dfu-programmer.exe" atmega32u4 erase
"/mnt/c/Program Files/dfu-programmer/dfu-programmer.exe" atmega32u4 flash Feuille64Midi.hex
"/mnt/c/Program Files/dfu-programmer/dfu-programmer.exe" atmega32u4 launch
echo "success!"