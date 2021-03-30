#include <iostream>
#include <memory>

#include "src/PuzzleBoard.h"
#include "src/PuzzlePiece.h"

using namespace PuzzleGame;

int
main(void) {
  std::vector<PuzzlePiece> player_pieces{PuzzlePiece({3, 0}, "Q1"), PuzzlePiece({3, 1}, "Q4"), PuzzlePiece({3, 2}, "Q3")};
  std::vector<PuzzlePiece> computer_pieces{PuzzlePiece({0, 0}, "q1"), PuzzlePiece({0, 1}, "q4"), PuzzlePiece({0, 2}, "q3")};
  std::vector<PuzzlePiece> inert_pieces{PuzzlePiece({1, 1}, "X")};
  std::vector<PuzzlePiece> sinks{PuzzlePiece({2, 2}, "s")};

  std::unique_ptr<PuzzleBoard> Board = std::unique_ptr<PuzzleBoard>(new PuzzleBoard(4, player_pieces, computer_pieces, inert_pieces, sinks));
  Board->PrintBoard();
}
