#!/bin/bash

#set -e

echo "rm build folder"
rm -fr build

echo "make the compilier env"
source /opt/fsl-imx-x11/4.1.15-2.0.1/environment-setup-cortexa9hf-neon-poky-linux-gnueabi

echo "mkdir build folder"
mkdir build

echo "cd build"
cd build

echo "cmake .."
cmake ..

echo "make"
make

#echo "copy files"
#cp src/libIKAlgoAPI.so ../../output/libIKAlgoAPI.so
