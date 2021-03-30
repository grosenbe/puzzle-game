cmake_minimum_required (VERSION 3.20.0)
set(CMAKE_CXX_FLAGS "-Wall -glldb")

project(puzzle-game)

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(demo)

