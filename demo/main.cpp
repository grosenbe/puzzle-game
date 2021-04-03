#include <getopt.h>

#include <iostream>
#include <memory>
#include <stdexcept>

#include "src/PuzzleBoard.h"
#include "src/PuzzlePiece.h"

using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::pair;
using std::string;
using std::vector;

using namespace PuzzleGame;

std::unique_ptr<PuzzleBoard> Board;
std::string InputFileName;

void
DisplayHelp() {
  cout << "Welcome to puzzle game. Options are:" << endl;
  cout << "-f: Path (full or relative) to an input file" << endl;
  cout << "-h: Display this help message" << endl;
}

void
ParseCommandLine(int argc, char** argv) {
  int c;

  while ((c = getopt(argc, argv, "f:h")) != -1)
    switch (c) {
      case 'f':
        InputFileName = optarg;
        break;
      case 'h':
        DisplayHelp();
        std::exit(0);
      default:
        std::cerr << "Unknown option. Exiting." << std::endl;
        std::exit(1);
    }
}

void
GetPlayerInput(std::string& piece, std::pair<uint32_t, uint32_t>& position) {
  bool selectionValidated = false;
  std::unordered_set<string> playerPieceNames = Board->GetPlayerPieceNames();
  while (!selectionValidated) {
    cout << "Available pieces to move:" << endl;
    for (const auto& n : playerPieceNames)
      cout << n << endl;

    std::cout << "Input: ";
    string userInput;
    cin >> userInput;
    if (cin.fail()) {
      cin.clear();
      cin.ignore();
      continue;
    }

    if (playerPieceNames.count(userInput) > 0) {
      piece = userInput;
      selectionValidated = true;
    } else {
      cout << "Piece " << userInput << " not available." << std::endl;
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
main(int argc, char** argv) {
  // If we are passed a file, use it. If we aren't, try to use the default file. If default file
  // isn't present, use the board below.
  if (argc > 0) {
    ParseCommandLine(argc, argv);
  }

  if (!InputFileName.empty()) {
    try {
      Board = std::unique_ptr<PuzzleBoard>(new PuzzleBoard(InputFileName));
    } catch (std::runtime_error& e) {
      cerr << "Caught runtime exception while creating board: " << e.what() << endl;
      abort();
    }
  } else {
    cout << "No input file. Using default board." << std::endl;

    vector<PuzzlePiece> player_pieces{PuzzlePiece({3, 0}, "Q1"), PuzzlePiece({3, 1}, "Q2"), PuzzlePiece({3, 2}, "Q3")};
    std::vector<PuzzlePiece> computer_pieces{PuzzlePiece({0, 0}, "q1"), PuzzlePiece({0, 1}, "q2"), PuzzlePiece({0, 2}, "q3")};
    std::vector<PuzzlePiece> inert_pieces{PuzzlePiece({1, 1}, "X")};
    std::vector<PuzzlePiece> sinks{PuzzlePiece({1, 2}, "s")};
    Board = std::unique_ptr<PuzzleBoard>(new PuzzleBoard(4, player_pieces, computer_pieces, inert_pieces, sinks));
  }

  while (!Board->CheckPuzzleCompletion()) {
    Board->PrintBoard();
    // get requested moves from the player
    string pieceToMove;
    pair<uint32_t, uint32_t> requestedPosition;
    GetPlayerInput(pieceToMove, requestedPosition);
    try {
      Board->PlayerMove(pieceToMove, requestedPosition);
    } catch (std::runtime_error& e) {
      cerr << "Caught runtime exception: " << e.what() << endl;
    }
  }

  Board->PrintBoard();
  cout << "You win!" << endl;
}
