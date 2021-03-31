cmake_minimum_required (VERSION 3.7.0)
add_compile_options(-Wall -Wextra -Wpedantic -Werror -glldb)
set(CMAKE_CXX_STANDARD 11)

project(puzzle-game)

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(demo)

