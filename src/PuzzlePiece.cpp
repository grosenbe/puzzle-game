#include "PuzzlePiece.h"

using namespace PuzzleGame;

std::unordered_map<Orientation, std::string> PuzzlePiece::OrientationToPlayerPieceName{{Orientation::Q1, "Q1"}, {Orientation::Q2, "Q2"}, {Orientation::Q3, "Q3"}, {Orientation::Q4, "Q4"}};
std::unordered_map<std::string, Orientation> PuzzlePiece::PlayerPieceNameToOrientation{{"Q1", Orientation::Q1}, {"Q2", Orientation::Q2}, {"Q3", Orientation::Q3}, {"Q4", Orientation::Q4}};

std::unordered_map<Orientation, std::string> PuzzlePiece::OrientationToComputerPieceName{
    {Orientation::q1, "q1"}, {Orientation::q2, "q2"}, {Orientation::q3, "q3"}, {Orientation::q4, "q4"}};
std::unordered_map<std::string, Orientation> PuzzlePiece::ComputerNameToOrientation{
    {"q1", Orientation::Q1}, {"q2", Orientation::Q2}, {"q3", Orientation::Q3}, {"q4", Orientation::Q4}};

std::unordered_map<Orientation, Orientation> PuzzlePiece::ComputerOrientationToPlayerOrientation{
    {Orientation::q1, Orientation::Q1}, {Orientation::q2, Orientation::Q2}, {Orientation::q3, Orientation::Q3}, {Orientation::q4, Orientation::Q4}};

std::unordered_map<Orientation, Orientation> PuzzlePiece::PlayerOrientationToComputerOrientation{
    {Orientation::Q1, Orientation::q1}, {Orientation::Q2, Orientation::q2}, {Orientation::Q3, Orientation::q3}, {Orientation::Q4, Orientation::q4}};

PuzzlePiece::PuzzlePiece(std::pair<uint32_t, uint32_t> position, std::string orientation) : Position{position} {
  Name = orientation;

  if (orientation == "Q1")
    Orientation = Orientation::Q1;
  else if (orientation == "q1")
    Orientation = Orientation::q1;

  else if (orientation == "Q2")
    Orientation = Orientation::Q2;
  else if (orientation == "q2")
    Orientation = Orientation::q2;

  else if (orientation == "Q3")
    Orientation = Orientation::Q3;
  else if (orientation == "q3")
    Orientation = Orientation::q3;

  else if (orientation == "Q4")
    Orientation = Orientation::Q4;
  else if (orientation == "q4")
    Orientation = Orientation::q4;

  else if (orientation == "X")
    Orientation = Orientation::X;
  else if (orientation == "s")
    Orientation = Orientation::S;
}

const std::string&
PuzzlePiece::GetName() const {
  return Name;
}

const std::pair<uint32_t, uint32_t>&
PuzzlePiece::GetPosition() const {
  return Position;
}

const ::Orientation&
PuzzlePiece::GetOrientation() const { return Orientation; }

void
PuzzlePiece::SetPosition(std::pair<uint32_t, uint32_t> newPosition) {
  Position = newPosition;
}
