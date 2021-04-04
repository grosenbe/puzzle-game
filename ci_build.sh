#!/usr/bin/env bash
[ ! -d "build" ] && mkdir build
rm -rf build/*
cd build
cmake -G "Unix Makefiles" -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_BUILD_TYPE=DEBUG ..
make package

test/puzzle-test
