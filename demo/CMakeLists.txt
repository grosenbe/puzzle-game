add_executable(puzzle-demo main.cpp)

target_include_directories(puzzle-demo PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/..)

target_link_libraries(puzzle-demo
  puzzle-game)
