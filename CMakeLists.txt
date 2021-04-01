cmake_minimum_required (VERSION 3.7.0)
if (CMAKE_CXX_COMPILER STREQUAL "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic -Werror -glldb)
  else()
  add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif()

set(CMAKE_CXX_STANDARD 11)

project(puzzle-game)

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(demo)

