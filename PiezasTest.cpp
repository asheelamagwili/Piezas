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

// Testing Constructor
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

TEST(PiezasTest, construct_nonblank_board)
{
	bool is_blank = true;
	Piezas my_game;
	my_game.dropPiece(0);
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
	EXPECT_EQ(is_blank, false);
}

