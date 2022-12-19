#!/bin/bash
cd engine
make clean
make
cd ../client
make clean
make
cd bin/Release
LD_LIBRARY_PATH=../../../engine/bin/Release/ ./client
