add_executable(puzzle-test puzzle-test.cpp)

target_include_directories(puzzle-test PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/..)

target_link_libraries(puzzle-test
  puzzle-game
  gtest
  pthread)
