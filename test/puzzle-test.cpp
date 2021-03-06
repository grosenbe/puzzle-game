#include <gtest/gtest.h>

#include <stdexcept>

#include "src/PuzzleBoard.h"
#include "src/PuzzlePiece.h"

using namespace PuzzleGame;
using std::vector;

class PuzzleTestFixture : public ::testing::Test {
 public:
  PuzzleTestFixture() {
    vector<PuzzlePiece> player_pieces{PuzzlePiece({3, 0}, "Q1"), PuzzlePiece({3, 1}, "Q4"), PuzzlePiece({3, 2}, "Q2")};
    vector<PuzzlePiece> computer_pieces{PuzzlePiece({0, 0}, "q1"), PuzzlePiece({0, 1}, "q4"), PuzzlePiece({0, 2}, "q2")};
    vector<PuzzlePiece> inert_pieces{PuzzlePiece({1, 1}, "X")};
    vector<PuzzlePiece> sinks{PuzzlePiece({2, 2}, "s")};

    Board = PuzzleBoard(4, player_pieces, computer_pieces, inert_pieces, sinks);
  }

  PuzzleBoard Board;
};

TEST_F(PuzzleTestFixture, CanGetPiecesFromBoard) {
  EXPECT_EQ(Board.GetPlayerPiece(Orientation::Q1).GetPosition().first, 3);
  EXPECT_EQ(Board.GetPlayerPiece(Orientation::Q1).GetPosition().second, 0);

  EXPECT_EQ(Board.GetPlayerPiece(Orientation::Q2).GetPosition().first, 3);
  EXPECT_EQ(Board.GetPlayerPiece(Orientation::Q2).GetPosition().second, 2);

  EXPECT_THROW(Board.GetPlayerPiece(Orientation::Q3), std::runtime_error);

  EXPECT_EQ(Board.GetPlayerPiece(Orientation::Q4).GetPosition().first, 3);
  EXPECT_EQ(Board.GetPlayerPiece(Orientation::Q4).GetPosition().second, 1);

  EXPECT_EQ(Board.GetComputerPiece(Orientation::q1).GetPosition().first, 0);
  EXPECT_EQ(Board.GetComputerPiece(Orientation::q1).GetPosition().second, 0);

  EXPECT_EQ(Board.GetComputerPiece(Orientation::q4).GetPosition().first, 0);
  EXPECT_EQ(Board.GetComputerPiece(Orientation::q4).GetPosition().second, 1);

  EXPECT_EQ(Board.GetComputerPiece(Orientation::q2).GetPosition().first, 0);
  EXPECT_EQ(Board.GetComputerPiece(Orientation::q2).GetPosition().second, 2);

  EXPECT_THROW(Board.GetComputerPiece(Orientation::q3), std::runtime_error);

  EXPECT_EQ(Board.GetInertPiece("X").GetPosition().first, 1);
  EXPECT_EQ(Board.GetInertPiece("X").GetPosition().second, 1);

  EXPECT_EQ(Board.GetSink("s").GetPosition().first, 2);
  EXPECT_EQ(Board.GetSink("s").GetPosition().second, 2);
}

TEST_F(PuzzleTestFixture, BoardHasCorrectNumberOfPieces) {
  EXPECT_EQ(Board.GetNumComputerPieces(), 3);
  EXPECT_EQ(Board.GetNumPlayerPieces(), 3);
  EXPECT_EQ(Board.GetNumInertPieces(), 1);
  EXPECT_EQ(Board.GetNumSinks(), 1);
}

TEST_F(PuzzleTestFixture, CannotMoveDiagonallyOrMoreThanOne) {
  EXPECT_THROW(Board.PlayerMove("Q1", {2, 1}), std::runtime_error);
  EXPECT_THROW(Board.PlayerMove("Q1", {3, 2}), std::runtime_error);
}

TEST_F(PuzzleTestFixture, CannotMovePieceOnTopOfAnother) {
  EXPECT_FALSE(Board.PlayerMove("Q1", {3, 1}));  // hits Q4
  EXPECT_TRUE(Board.PlayerMove("Q1", {2, 0}));
  EXPECT_FALSE(Board.PlayerMove("Q1", {1, 0}));  // hits q1
  EXPECT_TRUE(Board.PlayerMove("Q1", {2, 1}));
  EXPECT_FALSE(Board.PlayerMove("Q1", {1, 1}));  // hits X
}

TEST_F(PuzzleTestFixture, CannotMoveComputerPiece) {
  EXPECT_THROW(Board.PlayerMove("q1", {1, 0}), std::runtime_error);
}

TEST_F(PuzzleTestFixture, LegalMoveUpdatesOccupiedPositionsAndSetsNewPosition) {
  EXPECT_TRUE(Board.OccupiedPositions.find({2, 0}) == Board.OccupiedPositions.end());
  EXPECT_EQ(Board.GetPlayerPiece(Orientation::Q1).GetPosition().first, 3);
  EXPECT_EQ(Board.GetPlayerPiece(Orientation::Q1).GetPosition().second, 0);

  EXPECT_EQ(Board.GetComputerPiece(Orientation::q1).GetPosition().first, 0);
  EXPECT_EQ(Board.GetComputerPiece(Orientation::q1).GetPosition().second, 0);

  EXPECT_TRUE(Board.PlayerMove("Q1", {2, 0}));
  EXPECT_FALSE(Board.OccupiedPositions.find({2, 0}) == Board.OccupiedPositions.end());

  EXPECT_EQ(Board.GetPlayerPiece(Orientation::Q1).GetPosition().first, 2);
  EXPECT_EQ(Board.GetPlayerPiece(Orientation::Q1).GetPosition().second, 0);

  EXPECT_EQ(Board.GetComputerPiece(Orientation::q1).GetPosition().first, 1);
  EXPECT_EQ(Board.GetComputerPiece(Orientation::q1).GetPosition().second, 0);
}

TEST(PuzzleTest, RequirePlayerPiecesAndSinks) {
  EXPECT_THROW(PuzzleBoard(2, {PuzzlePiece({0, 0}, "Q1")}, {PuzzlePiece({1, 0}, "q1")}, vector<PuzzlePiece>{}, vector<PuzzlePiece>{}), std::runtime_error);
  EXPECT_THROW(PuzzleBoard(2, vector<PuzzlePiece>{}, vector<PuzzlePiece>{}, vector<PuzzlePiece>{}, {PuzzlePiece({1, 1}, "s")}), std::runtime_error);
}

TEST(PuzzleTest, CheckCompletionReturnsAppropriately) {
  PuzzleBoard board1(2, {PuzzlePiece({1, 1}, "Q2")}, {PuzzlePiece({0, 0}, "q2")}, vector<PuzzlePiece>{}, {PuzzlePiece({0, 1}, "s")});
  EXPECT_TRUE(board1.CheckPuzzleCompletion());

  PuzzleBoard board2(3, {PuzzlePiece({2, 0}, "Q2"), PuzzlePiece({0, 0}, "Q4")}, {PuzzlePiece({1, 1}, "q2"), PuzzlePiece({2, 2}, "q4")}, vector<PuzzlePiece>{}, {PuzzlePiece({0, 2}, "s")});
  EXPECT_TRUE(board2.CheckPuzzleCompletion());

  PuzzleBoard board3(2, {PuzzlePiece({1, 0}, "Q4")}, {PuzzlePiece({0, 0}, "q4")}, vector<PuzzlePiece>{}, {PuzzlePiece({1, 1}, "s")});
  EXPECT_FALSE(board3.CheckPuzzleCompletion());
}

TEST(PuzzleTest, CannotPlacePiecesOutsideBoard) {
  vector<PuzzlePiece> player_piece_outside{PuzzlePiece({3, 0}, "Q1")};
  vector<PuzzlePiece> player_piece{PuzzlePiece({2, 0}, "Q1")};
  vector<PuzzlePiece> computer_piece_outside{PuzzlePiece({3, 0}, "q1")};
  vector<PuzzlePiece> computer_piece{PuzzlePiece({2, 0}, "q1")};
  vector<PuzzlePiece> inert_pieces{PuzzlePiece({1, 1}, "X")};
  vector<PuzzlePiece> sinks{PuzzlePiece({2, 2}, "s")};

  EXPECT_THROW(PuzzleBoard board(3, player_piece_outside, computer_piece, inert_pieces, sinks), std::runtime_error);
  EXPECT_THROW(PuzzleBoard board(3, player_piece, computer_piece_outside, inert_pieces, sinks), std::runtime_error);
}

TEST(PuzzleTest, EqualNumberOfPlayerAndComputerPieces) {
  vector<PuzzlePiece> player_pieces{PuzzlePiece({3, 0}, "Q1")};
  vector<PuzzlePiece> computer_pieces{PuzzlePiece({0, 0}, "q1"), PuzzlePiece({0, 1}, "q4")};
  vector<PuzzlePiece> inert_pieces{PuzzlePiece({1, 1}, "X")};
  vector<PuzzlePiece> sinks{PuzzlePiece({2, 2}, "s")};

  EXPECT_THROW(PuzzleBoard board(4, player_pieces, computer_pieces, inert_pieces, sinks), std::runtime_error);
}

TEST(PuzzleTest, MatchingComputerPieceOrientationForEachPlayerPiece) {
  vector<PuzzlePiece> player_pieces{PuzzlePiece({3, 0}, "Q1")};
  vector<PuzzlePiece> computer_pieces{PuzzlePiece({0, 0}, "q4")};
  vector<PuzzlePiece> inert_pieces{PuzzlePiece({1, 1}, "X")};
  vector<PuzzlePiece> sinks{PuzzlePiece({2, 2}, "s")};

  EXPECT_THROW(PuzzleBoard board(4, player_pieces, computer_pieces, inert_pieces, sinks), std::runtime_error);
}

TEST(PuzzleTest, NoStackedPieces) {
  vector<PuzzlePiece> player_pieces{PuzzlePiece({3, 0}, "Q1"), PuzzlePiece({3, 0}, "Q1")};
  vector<PuzzlePiece> computer_pieces{PuzzlePiece({3, 0}, "q1")};
  vector<PuzzlePiece> inert_pieces{PuzzlePiece({1, 1}, "X")};
  vector<PuzzlePiece> sinks{PuzzlePiece({2, 2}, "s")};

  EXPECT_THROW(PuzzleBoard board(4, player_pieces, computer_pieces, inert_pieces, sinks), std::runtime_error);
}

TEST(PuzzleTest, CantMoveComputerPieceOffBoard) {
  vector<PuzzlePiece> player_pieces{PuzzlePiece({2, 0}, "Q1")};
  vector<PuzzlePiece> computer_pieces{PuzzlePiece({0, 0}, "q1")};
  vector<PuzzlePiece> inert_pieces{PuzzlePiece({1, 1}, "X")};
  vector<PuzzlePiece> sinks{PuzzlePiece({2, 2}, "s")};

  PuzzleBoard board(4, player_pieces, computer_pieces, inert_pieces, sinks);
  board.PlayerMove("Q1", {3, 0});

  EXPECT_EQ(board.GetComputerPiece(Orientation::q1).GetPosition().first, 0);
  EXPECT_EQ(board.GetComputerPiece(Orientation::q1).GetPosition().second, 0);
}

TEST(PuzzleTest, AdjacentPieces) {
  vector<PuzzlePiece> player_pieces{PuzzlePiece({2, 2}, "Q2"), PuzzlePiece({1, 2}, "Q3")};
  vector<PuzzlePiece> computer_pieces{PuzzlePiece({0, 0}, "q2"), PuzzlePiece({0, 1}, "q3")};
  vector<PuzzlePiece> sinks{PuzzlePiece({1, 1}, "s")};
  PuzzleBoard board(3, player_pieces, computer_pieces, vector<PuzzlePiece>(), sinks);
  EXPECT_TRUE(board.CheckPuzzleCompletion());
}

TEST(PuzzleTest, EdgeOfBoard) {
  vector<PuzzlePiece> player_pieces{PuzzlePiece({2, 2}, "Q2")};
  vector<PuzzlePiece> computer_pieces{PuzzlePiece({0, 0}, "q2")};
  vector<PuzzlePiece> sinks{PuzzlePiece({1, 1}, "s")};
  PuzzleBoard board(3, player_pieces, computer_pieces, vector<PuzzlePiece>(), sinks);
  EXPECT_FALSE(board.CheckPuzzleCompletion());
}

TEST(PuzzleTest, BeamStartsOutOnPiece) {
  vector<PuzzlePiece> player_pieces{PuzzlePiece({2, 0}, "Q2")};
  vector<PuzzlePiece> computer_pieces{PuzzlePiece({0, 0}, "q2")};
  vector<PuzzlePiece> sinks{PuzzlePiece({1, 0}, "s")};
  PuzzleBoard board(3, player_pieces, computer_pieces, vector<PuzzlePiece>(), sinks);
  EXPECT_TRUE(board.CheckPuzzleCompletion());
}

TEST(PuzzleTest, TripleReflectionWorks) {
  vector<PuzzlePiece> player_pieces{PuzzlePiece({3, 0}, "Q2"), PuzzlePiece({0, 0}, "Q4"), PuzzlePiece({0, 2}, "Q3")};
  vector<PuzzlePiece> computer_pieces{PuzzlePiece({3, 1}, "q2"), PuzzlePiece({3, 2}, "q4"), PuzzlePiece({2, 1}, "q3")};
  vector<PuzzlePiece> sinks{PuzzlePiece({1, 2}, "s")};
  PuzzleBoard board(4, player_pieces, computer_pieces, vector<PuzzlePiece>(), sinks);
  EXPECT_TRUE(board.CheckPuzzleCompletion());
}

TEST(PuzzleTest, ThowWhenCreatingBoardWithNoSink) {
  vector<PuzzlePiece> player_pieces{PuzzlePiece({3, 0}, "Q2"), PuzzlePiece({0, 0}, "Q4"), PuzzlePiece({0, 2}, "Q3")};
  vector<PuzzlePiece> computer_pieces{PuzzlePiece({3, 1}, "q2"), PuzzlePiece({3, 2}, "q4"), PuzzlePiece({2, 1}, "q3")};

  EXPECT_THROW(PuzzleBoard board(4, player_pieces, computer_pieces, vector<PuzzlePiece>(), vector<PuzzlePiece>()), std::runtime_error);
}

TEST(PuzzleTest, ConstructBoardFromInputFile) {
  EXPECT_THROW(PuzzleBoard("/does/not/exist"), std::runtime_error);

  PuzzleBoard board("../test/test_input_files/test_input.txt");
  EXPECT_EQ(board.GetPlayerPiece(Orientation::Q1).GetPosition().first, 3);
  EXPECT_EQ(board.GetPlayerPiece(Orientation::Q1).GetPosition().second, 0);

  EXPECT_EQ(board.GetPlayerPiece(Orientation::Q2).GetPosition().first, 3);
  EXPECT_EQ(board.GetPlayerPiece(Orientation::Q2).GetPosition().second, 1);

  EXPECT_EQ(board.GetPlayerPiece(Orientation::Q3).GetPosition().first, 3);
  EXPECT_EQ(board.GetPlayerPiece(Orientation::Q3).GetPosition().second, 2);

  EXPECT_EQ(board.GetSink("s").GetPosition().first, 1);
  EXPECT_EQ(board.GetSink("s").GetPosition().second, 2);

  EXPECT_EQ(board.GetInertPiece("X").GetPosition().first, 1);
  EXPECT_EQ(board.GetInertPiece("X").GetPosition().second, 1);

  EXPECT_EQ(board.GetComputerPiece(Orientation::q1).GetPosition().first, 0);
  EXPECT_EQ(board.GetComputerPiece(Orientation::q1).GetPosition().second, 0);

  EXPECT_EQ(board.GetComputerPiece(Orientation::q2).GetPosition().first, 0);
  EXPECT_EQ(board.GetComputerPiece(Orientation::q2).GetPosition().second, 1);

  EXPECT_EQ(board.GetComputerPiece(Orientation::q3).GetPosition().first, 0);
  EXPECT_EQ(board.GetComputerPiece(Orientation::q3).GetPosition().second, 2);
}

TEST(PuzzleTest, ThrowOnBadInputFiles) {
  EXPECT_THROW(PuzzleBoard("../test/test_input_files/misformatted.txt"), std::runtime_error);
  EXPECT_THROW(PuzzleBoard("../test/test_input_files/misformatted2.txt"), std::runtime_error);
  EXPECT_THROW(PuzzleBoard("../test/test_input_files/misformatted3.txt"), std::runtime_error);
}

int
main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
