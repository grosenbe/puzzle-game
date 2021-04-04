#!/usr/bin/env bash
sudo apt-get install ninja-build googletest valgrind

export CC=$(which clang)
export CXX=$(which clang++)

# install googletest
sudo mkdir /usr/src/googletest/build
cd /usr/src/googletest/build
sudo cmake -G "Ninja" ..
sudo ninja
sudo ninja install
cd -

mkdir build
cd build
cmake -G "Ninja" ..
ninja package

valgrind test/puzzle-test
