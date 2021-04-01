#include "PuzzleBoard.h"

#include <cmath>
#include <iostream>
#include <stdexcept>
#include <string>

#include "PuzzlePiece.h"

using std::string;
using std::vector;
using namespace PuzzleGame;

const size_t PuzzleBoard::SQUARE_WIDTH = 3;

PuzzleBoard::PuzzleBoard(uint32_t size, const vector<PuzzlePiece> &player, const vector<PuzzlePiece> &computer, const vector<PuzzlePiece> &inert, const vector<PuzzlePiece> &sinks) : BoardSize(size) {
  if (computer.size() != player.size())
    throw std::runtime_error("Different number of player and computer pieces");

  for (const auto &pl : player) {
    if (pl.GetPosition().first < BoardSize && pl.GetPosition().second < BoardSize) {
      if (OccupiedPositions.find(pl.GetPosition()) != OccupiedPositions.end())
        throw std::runtime_error("Error: Stacked pieces");
      PlayerPieces.insert({pl.GetOrientation(), pl});
      OccupiedPositions.insert(pl.GetPosition());
    } else {
      throw std::runtime_error("Player piece placed outside board");
    }
  }

  for (const auto &cp : computer) {
    if (cp.GetPosition().first < BoardSize && cp.GetPosition().second < BoardSize) {
      if (PlayerPieces.find(PuzzlePiece::ComputerOrientationToPlayerOrientation[cp.GetOrientation()]) != PlayerPieces.end()) {
        if (OccupiedPositions.find(cp.GetPosition()) != OccupiedPositions.end())
          throw std::runtime_error("Error: Stacked pieces");
        ComputerPieces.insert({cp.GetOrientation(), cp});
        OccupiedPositions.insert(cp.GetPosition());
      } else {
        std::string triedToFind = PuzzlePiece::OrientationToComputerPieceName[cp.GetOrientation()];
        throw std::runtime_error("No matching player piece for this computer piece: " + triedToFind);
      }
    } else {
      throw std::runtime_error("Computer piece placed outside board");
    }
  }

  for (const auto &in : inert) {
    if (in.GetPosition().first < BoardSize && in.GetPosition().second < BoardSize) {
      if (OccupiedPositions.find(in.GetPosition()) != OccupiedPositions.end())
        throw std::runtime_error("Error: Stacked pieces");
      InertPieces.insert({in.GetName(), in});
      OccupiedPositions.insert(in.GetPosition());
    } else {
      throw std::runtime_error("Inert piece placed outside board");
    }
  }

  for (const auto &sy : sinks) {
    if (sy.GetPosition().first < BoardSize && sy.GetPosition().second < BoardSize) {
      if (OccupiedPositions.find(sy.GetPosition()) != OccupiedPositions.end())
        throw std::runtime_error("Error: Stacked pieces");
      Sinks.insert({sy.GetName(), sy});
      OccupiedPositions.insert(sy.GetPosition());
    } else {
      throw std::runtime_error("Sink placed outside board");
    }
  }
}

void
PuzzleBoard::PrintFillerRow() {
  std::cout << "   +";
  for (size_t c = 0; c < BoardSize; ++c) {
    for (size_t ch = 0; ch < PuzzleBoard::SQUARE_WIDTH; ++ch)
      std::cout << "-";
    std::cout << "+";
  }
  std::cout << std::endl;
}

void
PuzzleBoard::PrintColumnHeaders() {
  string leftPadding((SQUARE_WIDTH - 2u) / 2 + 1, ' ');
  string rightPadding((SQUARE_WIDTH - 2u) / 2 + 1, ' ');
  std::cout << "   ";
  for (auto c = 0u; c < BoardSize; ++c) {
    std::cout << leftPadding << "C" << c << rightPadding;
  }
  std::cout << std::endl;
}

void
PuzzleBoard::PrintContentRow(const std::vector<std::string> &row, size_t rowNum) {
  for (auto c = 0u; c < row.size(); ++c) {
    if (c == 0)
      std::cout << "R" << rowNum << " |";
    const auto &str = row[c];
    std::string outStr(PuzzleBoard::SQUARE_WIDTH, ' ');
    if (str.size() == 1) {
      if (PuzzleBoard::SQUARE_WIDTH % 2u)
        outStr[PuzzleBoard::SQUARE_WIDTH / 2u] = str[0];
      else
        outStr[PuzzleBoard::SQUARE_WIDTH / 2u - 1] = str[0];

    } else if (str.size() == 2) {
      if (PuzzleBoard::SQUARE_WIDTH % 2u) {
        outStr[PuzzleBoard::SQUARE_WIDTH / 2u - 1] = str[0];
        outStr[PuzzleBoard::SQUARE_WIDTH / 2u + 1] = str[1];
      } else {
        outStr[PuzzleBoard::SQUARE_WIDTH / 2u] = str[0];
        outStr[PuzzleBoard::SQUARE_WIDTH / 2u + 1] = str[1];
      }
    }
    std::cout << outStr << "|";
  }
  std::cout << std::endl;
}

// Example board:
//       C0    C1    C2    C3    C4
//    +-----+-----+-----+-----+-----+
// R0 | q 1 | q 2 | q 3 | q 4 |     |
//    +-----+-----+-----+-----+-----+
// R1 |     |  X  |     |     |     |
//    +-----+-----+-----+-----+-----+
// R2 |     |     |  s  |     |     |
//    +-----+-----+-----+-----+-----+
// R3 |     |     |     |     |     |
//    +-----+-----+-----+-----+-----+
// R4 |     | Q 1 | Q 2 | Q 3 | Q 4 |
//    +-----+-----+-----+-----+-----+
//
void
PuzzleBoard::PrintBoard() {
  vector<vector<string>> board;
  for (auto s = 0u; s < BoardSize; ++s) {
    board.push_back(vector<string>(BoardSize, ""));
  }

  for (auto &p : PlayerPieces) {
    auto pos = p.second.GetPosition();
    board[pos.first][pos.second] = PuzzlePiece::OrientationToPlayerPieceName[p.first];
  }

  for (auto &p : ComputerPieces) {
    auto pos = p.second.GetPosition();
    board[pos.first][pos.second] = PuzzlePiece::OrientationToComputerPieceName[p.first];
  }

  for (auto &p : InertPieces) {
    auto pos = p.second.GetPosition();
    board[pos.first][pos.second] = p.first;
  }

  for (auto &sn : Sinks) {
    auto pos = sn.second.GetPosition();
    board[pos.first][pos.second] = sn.first;
  }

  PrintColumnHeaders();
  PrintFillerRow();
  for (size_t r = 0; r < BoardSize; ++r) {
    PrintContentRow(board[r], r);
    PrintFillerRow();
  }
}

bool
PuzzleBoard::PlayerMove(const std::string &pieceName, std::pair<uint32_t, uint32_t> newPosition) {
  auto it = PlayerPieces.find(PuzzlePiece::PlayerPieceNameToOrientation[pieceName]);
  if (it == PlayerPieces.end()) {
    throw std::runtime_error("Cannot move player piece " + pieceName + " because it does not exist.");
  }

  auto currentPosition = it->second.GetPosition();
  int32_t dy = newPosition.first - currentPosition.first;
  int32_t dx = newPosition.second - currentPosition.second;
  // Make sure we're only moving by 1 space
  if (std::abs(dx) > 1 || std::abs(dy) > 1 || (std::abs(dx) == 1 && std::abs(dy) == 1))
    throw std::runtime_error("Cannot move by more than one space");

  // Make sure the new space is on the board
  if (newPosition.first > BoardSize - 1 || newPosition.second > BoardSize - 1)
    return false;

  // Make sure the new space isn't occupied
  if (OccupiedPositions.find(newPosition) != OccupiedPositions.end())
    return false;

  // move player piece
  it->second.SetPosition(newPosition);

  // Update OccupiedPositions
  OccupiedPositions.erase(currentPosition);
  OccupiedPositions.insert(newPosition);

  auto it2 = ComputerPieces.find(PuzzlePiece::PlayerOrientationToComputerOrientation[PuzzlePiece::PlayerPieceNameToOrientation[pieceName]]);
  auto currentComputerPosition = it2->second.GetPosition();
  auto newComputerPosition = currentComputerPosition;
  if (static_cast<int32_t>(currentComputerPosition.second) + dx >= 0 || currentComputerPosition.second + dx < BoardSize)
    newComputerPosition.second = currentComputerPosition.second + dx;
  if (static_cast<int32_t>(currentComputerPosition.first) - dy >= 0 || currentComputerPosition.first - dy < BoardSize)
    newComputerPosition.first = currentComputerPosition.first - dy;

  if (OccupiedPositions.find(newComputerPosition) == OccupiedPositions.end()) {
    it2->second.SetPosition(newComputerPosition);
    OccupiedPositions.erase(currentComputerPosition);
    OccupiedPositions.insert(newComputerPosition);
  }

  return true;
}

bool
PuzzleBoard::CheckPuzzleCompletion() {
  bool finished = false;
  bool puzzleComplete = false;
  auto currentBeamDirection = Direction::Right;
  auto currentBeamPosition = std::pair<uint32_t, uint32_t>{BoardSize - 1, 0};

  // handle cases where the beam *starts out* on a player piece (IE there's a player piece on the bottom left of the board)
  for (auto &pl : PlayerPieces) {
    bool cont = true;
    while (pl.second.GetPosition() == currentBeamPosition && cont) {
      // hit a player piece.
      auto originalNextPosition = currentBeamPosition;
      UpdateBeamDirectionAndPosition(currentBeamDirection, currentBeamPosition, pl.second);
      if (currentBeamPosition == originalNextPosition) {
        cont = false;  // this happens if we hit the back of a player piece
        finished = true;
      }
      currentBeamPosition = originalNextPosition;
      cont = false;
    }
  }

  while (!finished) {
    std::pair<uint32_t, uint32_t> potentialNextPosition = currentBeamPosition;

    switch (currentBeamDirection) {
      case Direction::Right:
        potentialNextPosition.second = currentBeamPosition.second + 1;
        break;

      case Direction::Left:
        if (currentBeamPosition.second > 0) {
          potentialNextPosition.second = currentBeamPosition.second - 1;
        } else {
          finished = true;
          continue;
        }
        break;

      case Direction::Up:
        if (currentBeamPosition.first > 0) {
          potentialNextPosition.first = currentBeamPosition.first - 1;
        } else {
          finished = true;
          continue;
        }
        break;

      case Direction::Down:
        potentialNextPosition.first = currentBeamPosition.first + 1;
        break;
    }

    if (potentialNextPosition.first >= BoardSize || potentialNextPosition.second >= BoardSize) {
      finished = true;  // off edge of board
      continue;
    }

    auto itr = OccupiedPositions.find(potentialNextPosition);
    if (itr == OccupiedPositions.end()) {
      currentBeamPosition = potentialNextPosition;
      continue;
    }

    // it's possible to have two player pieces directly next to each other, so the beam reflects
    // from one player piece directly into another
    bool reflected = true;  // reflected directly onto another player piece
    while (reflected) {
      reflected = false;
      auto originalNextPosition = potentialNextPosition;
      for (auto &pl : PlayerPieces) {
        if (pl.second.GetPosition() == potentialNextPosition) {
          //hit a player piece
          reflected = true;
          UpdateBeamDirectionAndPosition(currentBeamDirection, potentialNextPosition, pl.second);
          if (potentialNextPosition == originalNextPosition) {
            finished = true;  // this happens if we hit the back of a player piece
            reflected = false;
            break;
          }
        }
      }
    }

    for (auto &cp : ComputerPieces) {
      if (cp.second.GetPosition() == potentialNextPosition) {
        finished = true;
        continue;
      }
    }

    for (auto &snk : Sinks) {
      if (snk.second.GetPosition() == potentialNextPosition) {
        puzzleComplete = true;
        finished = true;
        continue;
      }
    }
    currentBeamPosition = potentialNextPosition;
  }

  return puzzleComplete;
}

void
PuzzleBoard::UpdateBeamDirectionAndPosition(Direction &beamDirection, std::pair<uint32_t, uint32_t> &beamPosition, const PuzzlePiece &piece) {
  // calculate the new direction and position based on the old direction.
  switch (piece.GetOrientation()) {
    case PuzzleGame::Orientation::Q1:
      if (beamDirection == Direction::Left) {
        beamDirection = Direction::Up;
        beamPosition = piece.GetPosition();
        --(beamPosition.first);
      } else if (beamDirection == Direction::Down) {
        beamDirection = Direction::Right;
        beamPosition = piece.GetPosition();
        ++(beamPosition.second);
      }
      break;
    case PuzzleGame::Orientation::Q2:
      if (beamDirection == Direction::Right) {
        beamDirection = Direction::Up;
        beamPosition = piece.GetPosition();
        --(beamPosition.first);
      } else if (beamDirection == Direction::Down) {
        beamDirection = Direction::Left;
        beamPosition = piece.GetPosition();
        --(beamPosition.second);  // TODO: What happens if beamPosition.second was already 0?
      }
      break;
    case PuzzleGame::Orientation::Q3:
      if (beamDirection == Direction::Right) {
        beamDirection = Direction::Down;
        beamPosition = piece.GetPosition();
        ++(beamPosition.first);
      } else if (beamDirection == Direction::Up) {
        beamDirection = Direction::Left;
        beamPosition = piece.GetPosition();
        --(beamPosition.second);
      }
      break;
    case PuzzleGame::Orientation::Q4:
      if (beamDirection == Direction::Left) {
        beamDirection = Direction::Down;
        beamPosition = piece.GetPosition();
        ++(beamPosition.first);
      } else if (beamDirection == Direction::Up) {
        beamDirection = Direction::Right;
        beamPosition = piece.GetPosition();
        ++(beamPosition.second);
      }
      break;
    default:
      break;
  }
}

size_t
PuzzleBoard::GetNumComputerPieces() {
  return ComputerPieces.size();
}

size_t
PuzzleBoard::GetNumPlayerPieces() {
  return PlayerPieces.size();
}

size_t
PuzzleBoard::GetNumInertPieces() {
  return InertPieces.size();
}

size_t
PuzzleBoard::GetNumSinks() {
  return Sinks.size();
}

const PuzzlePiece &
PuzzleBoard::GetPlayerPiece(const Orientation &orientation) {
  auto it = PlayerPieces.find(orientation);
  if (it == PlayerPieces.end()) {
    throw std::runtime_error("No such player piece on the board.");
  }
  return it->second;
}

const PuzzlePiece &
PuzzleBoard::GetComputerPiece(const Orientation &orientation) {
  auto it = ComputerPieces.find(orientation);
  if (it == ComputerPieces.end()) {
    throw std::runtime_error("No such computer piece on the board.");
  }
  return it->second;
}

const PuzzlePiece &
PuzzleBoard::GetInertPiece(const std::string &name) {
  auto it = InertPieces.find(name);
  if (it == InertPieces.end()) {
    throw std::runtime_error("No such inert piece on the board.");
  }
  return it->second;
}

const PuzzlePiece &
PuzzleBoard::GetSink(const std::string &name) {
  auto it = Sinks.find(name);
  if (it == Sinks.end()) {
    throw std::runtime_error("No such sink on the board.");
  }
  return it->second;
}
