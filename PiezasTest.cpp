/**
 * Unit Tests for Piezas
**/

#include <gtest/gtest.h>
#include "Piezas.h"
 
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

// Constructors
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
				cout<<"["<<i<<"]"<<"["<<j<<"]"<<endl;
			}
		}
	}
	ASSERT_TRUE(is_blank);
}