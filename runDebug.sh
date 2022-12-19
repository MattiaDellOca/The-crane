#!/bin/bash
cd engine
make clean
make
cd ../client
make clean
make
cd bin/Debug
LD_LIBRARY_PATH=../../../engine/bin/Debug/ ./client
