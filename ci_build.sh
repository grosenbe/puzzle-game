#!/usr/bin/env bash
sudo apt-get install clang-11 ninja-build googletest

export CC=$(which clang)
export CXX=$(which clang++)

[ ! -d "build" ] && mkdir build
rm -rf build/*
cd build
cmake -G "Ninja" -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_BUILD_TYPE=DEBUG ..
ninja package

test/puzzle-test
