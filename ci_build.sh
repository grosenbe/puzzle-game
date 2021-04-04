#!/usr/bin/env bash
sudo apt install clang++ ninja googletest

export CC=$(which clang)
export CXX=$(which clang++)

[ ! -d "build" ] && mkdir build
rm -rf build/*
cd build
cmake -G "Ninja" -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_BUILD_TYPE=DEBUG ..
make package

test/puzzle-test
