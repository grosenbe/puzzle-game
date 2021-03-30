set(Sources PuzzlePiece.cpp PuzzleBoard.cpp)

add_library(puzzle-game ${Sources})

target_include_directories(puzzle-game PUBLIC ${CMAKE_SURRENT_SOURCE_DIR})
