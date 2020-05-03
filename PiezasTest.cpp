/**
 * Unit Tests for Piezas
**/

#include <gtest/gtest.h>
#include "Piezas.h"

using namespace std;
 
class PiezasTest : public ::testing::Test
{
	protected:
		PiezasTest(){} //constructor runs before each test
		virtual ~PiezasTest(){} //destructor cleans up after tests
		virtual void SetUp(){} //sets up before each test (after constructor)
		virtual void TearDown(){} //clean up after each test, (before destructor) 
};

TEST(PiezasTest, sanityCheck)
{
	ASSERT_TRUE(true);
}

/* ----- Testing Constructor ----- */

// Construct a blank board
TEST(PiezasTest, construct_blank_board)
{
	bool is_blank = true;
	Piezas my_game;
	
	for(int i = 0; i < 3; i++)
	{
		for(int j = 0;j < 4; j++)
		{
			if(my_game.pieceAt(i,j) != ' ')
			{
				is_blank = false;
			}
		}
	}
	EXPECT_EQ(is_blank, true);
}

/* ----- Testing DropPiece ----- */

// Detects out-of-bounds in the positive range
TEST(PiezasTest, out_of_bounds_positive)
{
	Piezas my_game;
	EXPECT_EQ(Invalid, my_game.dropPiece(10));
}

// Detects out-of-bounds in the positive range after two turns
TEST(PiezasTest, out_of_bounds_positive_on_second_turn)
{
	Piezas my_game;
	// X loses their turn
	my_game.dropPiece(10);
	// O loses their turn
	EXPECT_EQ(Invalid, my_game.dropPiece(4));
}

// Detects out-of-bounds in the negative range
TEST(PiezasTest, out_of_bounds_negative)
{
	Piezas my_game;
	EXPECT_EQ(Invalid, my_game.dropPiece(-2));
}

// Toggles turn after out-of-bound location (X -> O)
TEST(PiezasTest, toggle_turn_after_oob)
{
	Piezas my_game;
	// Drop out-of-bound piece (X)
	my_game.dropPiece(5);
	// Next player takes turn (O)
	Piece val = my_game.dropPiece(0);
	EXPECT_EQ(O, val);
}

// Detects full column
TEST(PiezasTest, full_column)
{
	Piezas my_game;
	my_game.dropPiece(0); // 1 - not full
	my_game.dropPiece(0); // 2 - not full
	my_game.dropPiece(0); // 3 - full

	EXPECT_EQ(Blank, my_game.dropPiece(0));
}

// Drops one piece in column 0
TEST(PiezasTest, drop_one_piece)
{
	Piezas my_game;
	EXPECT_EQ(X, my_game.dropPiece(0));
}

// Toggles next turn after one turns
TEST(PiezasTest, toggles_one_turn)
{
	Piezas my_game;
	// X's turn
	Piece current_turn = my_game.dropPiece(0);
	// O's turn
	EXPECT_EQ(O, my_game.dropPiece(1));
}

// Toggles next turn after two turns
TEST(PiezasTest, toggles_two_turns)
{
	Piezas my_game;
	// X's turn
	my_game.dropPiece(0);
	// O's turn
	my_game.dropPiece(1);
	// X's turn again
	EXPECT_EQ(X, my_game.dropPiece(2));
}

// Fills an entire column
TEST(PiezasTest, fill_entire_column)
{
	Piezas my_game;
	// X's turn
	EXPECT_EQ(X, my_game.dropPiece(0));
	// O's turn
	EXPECT_EQ(O, my_game.dropPiece(0));
	// X's turn again
	EXPECT_EQ(X, my_game.dropPiece(0));
}

/* ----- Testing pieceAt ----- */

// Returns blank piece on empty board
TEST(PiezasTest, blank_board_and_piece)
{
	Piezas my_game;
	EXPECT_EQ(Blank, my_game.pieceAt(0,0));
}

// Returns X after one turn
TEST(PiezasTest, returns_piece_X)
{
	Piezas my_game;
	my_game.dropPiece(0);
	EXPECT_EQ(X, my_game.pieceAt(0,0));
}

// Returns O after two turns
TEST(PiezasTest, returns_piece_O)
{
	Piezas my_game;
	my_game.dropPiece(0);
	my_game.dropPiece(0);
	EXPECT_EQ(O, my_game.pieceAt(1,0));
}

// Returns Invalid when pieceAt() is given out of bounds coordinates for row
TEST(PiezasTest, returns_piece_O)
{
	Piezas my_game;
	EXPECT_EQ(Invalid, my_game.pieceAt(5,0));
}