#!/bin/bash
cd engine
make clean
make compile_debug
cd ../client
make clean
make compile_debug
cd ../Debug
./client_static
