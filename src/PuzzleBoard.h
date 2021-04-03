#ifndef PUZZLEBOARD_H_
#define PUZZLEBOARD_H_

#include <cstdint>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "PuzzlePiece.h"

using std::string;
using std::vector;

// directions the beam can be traveling
enum class Direction : char {
  Up,
  Down,
  Left,
  Right
};

namespace PuzzleGame {
class PuzzleBoard {
 public:
  PuzzleBoard(uint32_t, const std::vector<PuzzlePiece> &, const std::vector<PuzzlePiece> &, const std::vector<PuzzlePiece> &, const std::vector<PuzzlePiece> &);
  PuzzleBoard() {}
  PuzzleBoard(const std::string &);

  uint32_t
  GetSize() {
    return BoardSize;
  }

  void PrintBoard() const;
  bool PlayerMove(const std::string &, std::pair<uint32_t, uint32_t>);
  std::set<std::pair<uint32_t, uint32_t>> OccupiedPositions;
  bool CheckPuzzleCompletion() const;
  void UpdateBeamDirectionAndPosition(Direction &, std::pair<uint32_t, uint32_t> &, const PuzzlePiece &) const;

  const std::unordered_set<string> GetPlayerPieceNames() const;

  size_t GetNumPlayerPieces() const;
  size_t GetNumComputerPieces() const;
  size_t GetNumInertPieces() const;
  size_t GetNumSinks() const;

  const PuzzlePiece &GetPlayerPiece(const Orientation &);
  const PuzzlePiece &GetComputerPiece(const Orientation &);
  const PuzzlePiece &GetInertPiece(const std::string &);
  const PuzzlePiece &GetSink(const std::string &);

 private:
  void Init(uint32_t, const std::vector<PuzzlePiece> &, const std::vector<PuzzlePiece> &, const std::vector<PuzzlePiece> &, const std::vector<PuzzlePiece> &);

  uint32_t BoardSize;  // board is square
  std::unordered_map<Orientation, PuzzlePiece> PlayerPieces;
  std::unordered_map<Orientation, PuzzlePiece> ComputerPieces;
  std::unordered_map<std::string, PuzzlePiece> InertPieces;
  std::unordered_map<std::string, PuzzlePiece> Sinks;

  static const size_t SQUARE_WIDTH;
  void PrintColumnHeaders() const;
  void PrintFillerRow() const;
  void PrintContentRow(const std::vector<std::string> &, const size_t) const;
};
}  // namespace PuzzleGame

#endif
