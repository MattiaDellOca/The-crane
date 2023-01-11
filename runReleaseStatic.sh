#!/bin/bash
cd engine
make clean
make compile_release
make test
cd ../client
make clean
make compile_release
cd ../Release
./client_static
