#ifndef PUZZLEBOARD_H_
#define PUZZLEBOARD_H_

#include <cstdint>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

#include "PuzzlePiece.h"

namespace PuzzleGame {
class PuzzleBoard {
 public:
  PuzzleBoard() {}
  PuzzleBoard(uint32_t, const std::vector<PuzzlePiece> &, const std::vector<PuzzlePiece> &, const std::vector<PuzzlePiece> &, const std::vector<PuzzlePiece> &);

  uint32_t
  GetSize() {
    return BoardSize;
  }

  void PrintBoard();
  bool PlayerMove(const std::string &, std::pair<uint32_t, uint32_t>);
  std::set<std::pair<uint32_t, uint32_t>> OccupiedPositions;
  bool CheckPuzzleCompletion();
  void UpdateBeamDirectionAndPosition(Direction &, std::pair<uint32_t, uint32_t> &, const PuzzlePiece &);

  size_t GetNumPlayerPieces();
  size_t GetNumComputerPieces();
  size_t GetNumInertPieces();
  size_t GetNumSinks();

  const PuzzlePiece &GetPlayerPiece(const Orientation &);
  const PuzzlePiece &GetComputerPiece(const Orientation &);
  const PuzzlePiece &GetInertPiece(const std::string &);
  const PuzzlePiece &GetSink(const std::string &);

 private:
  uint32_t BoardSize;  // board is square
  std::unordered_map<Orientation, PuzzlePiece> PlayerPieces;
  std::unordered_map<Orientation, PuzzlePiece> ComputerPieces;
  std::unordered_map<std::string, PuzzlePiece> InertPieces;
  std::unordered_map<std::string, PuzzlePiece> Sinks;

  static const size_t SQUARE_WIDTH;
  void PrintColumnHeaders();
  void PrintFillerRow();
  void PrintContentRow(const std::vector<std::string> &, const size_t);
};
};  // namespace PuzzleGame

#endif
