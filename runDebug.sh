#!/bin/bash
cd graphicsEngine
make clean
make
cd ../client
make clean
make
cd bin/Debug
LD_LIBRARY_PATH=../../../graphicsEngine/bin/Debug/ ./client
