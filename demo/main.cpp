#include <iostream>
#include <memory>

#include "src/PuzzleBoard.h"
#include "src/PuzzlePiece.h"

using std::cin;
using std::cout;
using std::endl;
using std::pair;
using std::string;
using std::vector;

using namespace PuzzleGame;

std::unique_ptr<PuzzleBoard> Board;

void
GetPlayerInput(std::string& piece, std::pair<uint32_t, uint32_t>& position) {
  bool selectionValidated = false;
  while (!selectionValidated) {
    cout << "Available pieces to move (select one):" << endl;
    cout << "1. Q1" << endl;
    cout << "2. Q2" << endl;
    cout << "3. Q3" << endl;

    int userInput;
    cin >> userInput;
    if (cin.fail()) {
      cin.clear();
      cin.ignore();
      continue;
    }

    switch (userInput) {
      case 1:
        piece = "Q1";
        cout << "Selected Q1" << endl;
        selectionValidated = true;
        break;
      case 2:
        piece = "Q2";
        cout << "Selected Q2" << endl;
        selectionValidated = true;
        break;
      case 3:
        piece = "Q3";
        cout << "Selected Q3" << endl;
        selectionValidated = true;
        break;
      default:
        cout << "Invalid input: " << userInput << endl;
    }
  }

  bool positionValidated = false;
  while (!positionValidated) {
    int32_t userRow, userCol;
    cout << "Enter new row: ";
    cin >> userRow;
    if (cin.fail()) {
      cin.clear();
      cin.ignore();
      continue;
    }

    cout << "Enter new column: ";
    cin >> userCol;
    if (cin.fail()) {
      cin.clear();
      cin.ignore();
      continue;
    }

    if (userRow >= 0 && static_cast<uint32_t>(userRow) < Board->GetSize() && userCol >= 0 && static_cast<uint32_t>(userCol) < Board->GetSize()) {
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
  std::vector<PuzzlePiece> sinks{PuzzlePiece({1, 2}, "s")};

  Board = std::unique_ptr<PuzzleBoard>(new PuzzleBoard(4, player_pieces, computer_pieces, inert_pieces, sinks));

  while (!Board->CheckPuzzleCompletion()) {
    Board->PrintBoard();
    // get requested moves from the player
    string pieceToMove;
    pair<uint32_t, uint32_t> requestedPosition;
    GetPlayerInput(pieceToMove, requestedPosition);
    try {
      Board->PlayerMove(pieceToMove, requestedPosition);
    } catch (std::runtime_error& e) {
      cout << "Caught runtime exception: " << e.what() << endl;
    }
  }

  Board->PrintBoard();
  cout << "You win!" << endl;
}
