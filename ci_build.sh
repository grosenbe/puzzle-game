#!/usr/bin/env bash
export CC=$(which clang)
export CXX=$(which clang++)

[ ! -d "build" ] && mkdir build
rm -rf build/*
cd build
cmake -G "Ninja" -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_BUILD_TYPE=DEBUG ..
ninja package

test/puzzle-test
