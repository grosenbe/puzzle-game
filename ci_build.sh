#!/usr/bin/env bash
sudo apt-get install ninja-build

export CC=$(which clang)
export CXX=$(which clang++)

mkdir build
cd build
cmake -G "Ninja" ..
ninja package

test/puzzle-test
