#!/usr/bin/env bash
sudo apt-get install clang-11 ninja-build googletest

export CC=$(which clang)
export CXX=$(which clang++)

mkdir /usr/src/googletest/build
cd /usr/src/googletest/build
cmake -G "Ninja" ..
ninja install
cd -

mkdir build
cd build
cmake -G "Ninja" ..
ninja package

test/puzzle-test
