#!/bin/bash
cd graphicsEngine
make clean
make
cd ../client
make clean
make
cd bin/Release
LD_LIBRARY_PATH=../../../graphicsEngine/bin/Release/ ./client
