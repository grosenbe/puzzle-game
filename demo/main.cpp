#include <iostream>
#include <memory>

#include "src/PuzzleBoard.h"
#include "src/PuzzlePiece.h"

using std::vector;

using namespace PuzzleGame;

void
GetPlayerInput(std::string& piece, std::pair<uint32_t, uint32_t>& position) {
  bool selectionValidated = false;
  while (!selectionValidated) {
    std::cout << "Available pieces to move (select one):" << std::endl;
    std::cout << "1. Q1" << std::endl;
    std::cout << "2. Q2" << std::endl;
    std::cout << "3. Q3" << std::endl;

    int userInput;
    std::cin >> userInput;

    switch (userInput) {
      case 1:
        piece = "Q1";
        std::cout << "Selected Q1" << std::endl;
        selectionValidated = true;
        break;
      case 2:
        piece = "Q2";
        std::cout << "Selected Q2" << std::endl;
        selectionValidated = true;
        break;
      case 3:
        piece = "Q3";
        std::cout << "Selected Q3" << std::endl;
        selectionValidated = true;
        break;
      default:
        std::cout << "Invalid input: " << userInput << std::endl;
    }
  }

  bool positionValidated = false;
  while (!positionValidated) {
    int32_t userRow, userCol;
    std::cout << "Enter new row: ";
    std::cin >> userRow;
    std::cout << "Enter new column: ";
    std::cin >> userCol;

    if (userRow >= 0 && userRow < 4 && userCol >= 0 && userCol < 4) {
      position.first = userRow;
      position.second = userCol;
      positionValidated = true;
    }
  }
}

int
main(int argc __attribute__((unused)), char** argv __attribute__((unused))) {
  vector<PuzzlePiece> player_pieces{PuzzlePiece({3, 0}, "Q1"), PuzzlePiece({3, 1}, "Q2"), PuzzlePiece({3, 2}, "Q3")};
  std::vector<PuzzlePiece> computer_pieces{PuzzlePiece({0, 0}, "q1"), PuzzlePiece({0, 1}, "q2"), PuzzlePiece({0, 2}, "q3")};
  std::vector<PuzzlePiece> inert_pieces{PuzzlePiece({1, 1}, "X")};
  std::vector<PuzzlePiece> sinks{PuzzlePiece({2, 2}, "s")};

  std::unique_ptr<PuzzleBoard> Board = std::unique_ptr<PuzzleBoard>(new PuzzleBoard(4, player_pieces, computer_pieces, inert_pieces, sinks));

  while (!Board->CheckPuzzleCompletion()) {
    Board->PrintBoard();
    // get requested moves from the player
    std::string pieceToMove;
    std::pair<uint32_t, uint32_t> requestedPosition;
    GetPlayerInput(pieceToMove, requestedPosition);
    try {
      Board->PlayerMove(pieceToMove, requestedPosition);
    } catch (std::runtime_error& e) {
      std::cout << "Caught runtime exception: " << e.what() << std::endl;
    }
  }

  Board->PrintBoard();
  std::cout << "You win!" << std::endl;
}
