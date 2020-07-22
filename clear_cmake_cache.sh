#!/bin/bash
# My first script
echo "deleting CMake Cache..."
rm -f CMakeCache.txt
rm -f Makefile
rm -f cmake_install.cmake
rm -rf CMakeFiles
rm -r ./bin/mp3_encoder
rm -r ./bin/*.mp3
clear
cmake .
make
cd ./bin/
./mp3_encoder .
cd ..
exec bash
echo "success..."

