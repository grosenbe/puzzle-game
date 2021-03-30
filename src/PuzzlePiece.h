#ifndef PUZZLEPIECE_H_
#define PUZZLEPIECE_H_

#include <cstdint>
#include <string>
#include <unordered_map>
#include <utility>

namespace PuzzleGame {
// Orientations for the mirror normal direction. These follow cartesian quadrants.
enum class Orientation : char {
  Q1,  // up and to the right (player piece)
  q1,  // up and to the right (computer piece)
  Q2,  // up and to the left
  q2,
  Q3,  // Down and to the left
  q3,
  Q4,  // down and to the right
  q4,
  S,  // sink
  X   // inert
};

class PuzzlePiece {
 public:
  PuzzlePiece(std::pair<uint32_t, uint32_t>, std::string);

  void SetPosition(std::pair<uint32_t, uint32_t>);
  const std::pair<uint32_t, uint32_t>& GetPosition() const;
  const Orientation& GetOrientation() const;
  const std::string& GetName() const;

  static std::unordered_map<Orientation, std::string> OrientationToPlayerPieceName;
  static std::unordered_map<std::string, Orientation> PlayerPieceNameToOrientation;

  static std::unordered_map<Orientation, std::string> OrientationToComputerPieceName;
  static std::unordered_map<std::string, Orientation> ComputerNameToOrientation;

  static std::unordered_map<Orientation, Orientation> ComputerOrientationToPlayerOrientation;
  static std::unordered_map<Orientation, Orientation> PlayerOrientationToComputerOrientation;

 private:
  std::pair<uint32_t, uint32_t> Position;
  Orientation Orientation;
  std::string Name;
};

// directions the beam can be traveling
enum class Direction : char {
  Up,
  Down,
  Left,
  Right
};

};  // namespace PuzzleGame
#endif
