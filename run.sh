#!/bin/bash
cd graphicsEngine
make clean
make
cd ../client
make clean
make
LD_LIBRARY_PATH=../graphicsEngine/ ./client 
