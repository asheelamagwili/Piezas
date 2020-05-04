#include "Piezas.h"
#include <vector>
#include <cmath> 
#include <iostream>

using namespace std;

/** CLASS Piezas
 * Class for representing a Piezas vertical board, which is roughly based
 * on the game "Connect Four" where pieces are placed in a column and 
 * fall to the bottom of the column, or on top of other pieces already in
 * that column. For an illustration of the board, see:
 *  https://en.wikipedia.org/wiki/Connect_Four
 *
 * Board coordinates [row,col] should match with:
 * [2,0][2,1][2,2][2,3]
 * [1,0][1,1][1,2][1,3]
 * [0,0][0,1][0,2][0,3]
 * So that a piece dropped in column 2 should take [0,2] and the next one
 * dropped in column 2 should take [1,2].
**/


/**
 * Constructor sets an empty board (default 3 rows, 4 columns) and 
 * specifies it is X's turn first
**/
Piezas::Piezas()
{
    // Initialize the size of the board
    board.resize(BOARD_ROWS);
    for(int i = 0;i < (int)board.size(); i++)
    {
        board[i].resize(BOARD_COLS);
    }

    // Initialize blank values
    for(int i = 0;i < (int)board.size(); i++)
    {
        for(int j = 0;j < (int)board[i].size(); j++)
        {
            board[i][j] = Blank;
        }
    }

    // Initialize X's initial turn
    turn = X;
}

/**
 * Resets each board location to the Blank Piece value, with a board of the
 * same size as previously specified
**/
void Piezas::reset()
{
    // Initialize the size of the board
    board.resize(BOARD_ROWS);
    for(int i = 0;i < (int)board.size(); i++)
    {
        board[i].resize(BOARD_COLS);
    }

    // Initialize blank values
    for(int i = 0;i < (int)board.size(); i++)
    {
        for(int j = 0;j < (int)board[i].size(); j++)
        {
            board[i][j] = Blank;
        }
    }

    // Reset the turn to X
    turn = X;
}

/**
 * Places a piece of the current turn on the board, returns what
 * piece is placed, and toggles which Piece's turn it is. dropPiece does 
 * NOT allow to place a piece in a location where a column is full.
 * In that case, placePiece returns Piece Blank value 
 * Out of bounds coordinates return the Piece Invalid value
 * Trying to drop a piece where it cannot be placed loses the player's turn
**/ 
Piece Piezas::dropPiece(int column)
{
    /* ----- Out-of-bounds Coordinates ----- */
    if(column >= BOARD_COLS || column < 0)
    {
        // Player loses turn
        if(turn == X)
        {
            turn = O;
        }
        else
        {
            turn = X;
        }
        
        return Invalid;
    }

    /* ----- Column is Full ----- */
    // Check from bottom to top if the column is full
    bool column_full = true;
    for(int k = BOARD_ROWS-1; k >= 0; k--)
    {
        if(board[k][column] == Blank)
        {
            column_full = false;
        }
    }

    if(column_full)
    {
        // Player loses turn
        if(turn == X)
        {
            turn = O;
        }
        else
        {
            turn = X;
        }
        return Blank;
    }

    /* ----- Valid Column ----- */
    // Place the value in the next available spot in given column
    for(int i = 2;i >= 0; i--)
    {
        if(board[i][column] == Blank)
        {
            board[i][column] = turn;
            // Next player's turn
            if(turn == X)
            {
                turn = O;
            }
            else
            {
                turn = X;
            }
            return board[i][column];
        }
    }
}

/**
 * Returns what piece is at the provided coordinates, or Blank if there
 * are no pieces there, or Invalid if the coordinates are out of bounds
**/
Piece Piezas::pieceAt(int row, int column)
{
    // Invert row
    row = abs(row - 2);

    // Out of bounds coordinates
    if((row >= BOARD_ROWS || row < 0) || (column >= BOARD_COLS || column < 0))
    {
        return Invalid;
    }

    // Valid coordinates
    return board[row][column];
}

/**
 * Returns which Piece has won, if there is a winner, Invalid if the game
 * is not over, or Blank if the board is filled and no one has won ("tie").
 * For a game to be over, all locations on the board must be filled with X's 
 * and O's (i.e. no remaining Blank spaces). The winner is which player has
 * the most adjacent pieces in a single line. Lines can go either vertically
 * or horizontally. If both X's and O's have the same max number of pieces in a
 * line, it is a tie.
**/
Piece Piezas::gameState()
{
    // Check if board is full
    bool is_full = true;
    int i, j;
    for(i = 0;i < (int)board.size(); i++)
    {
        for(j = 0;j < (int)board[i].size(); j++)
        {
            if(board[i][j] == Blank)
            {
                is_full = false;
            }
        }
    }

    // If board is full, check for the winner
    if(is_full)
    {
        int x_max = 0; // Track X's longest streak
        int o_max = 0; // Track O's longest streak
        Piece cur_lead = Blank; // Track which one is currently in the lead
        Piece lead = Blank;
        int lead_streak = 0;

        // Search horizontally
        for(i = 0;i < (int)board.size(); i++)
        {
            for(j = 0;j < (int)board[i].size(); j++)
            {
                // Count streaks
                if(board[i][j] == X)
                    x_max++;
                else if(board[i][j] == O)
                    o_max++;
            }

            cout<<"X: "<<x_max<<endl;
            cout<<"O: "<<o_max<<endl;

            // Update who is in the lead after each row & reset
            if(x_max > o_max && x_max > lead_streak)
            {
                cur_lead = X;
                lead_streak = x_max;
                x_max = 0;
                o_max = 0;
            }
            else if(o_max > x_max && o_max > lead_streak)
            {
                cur_lead = O;
                lead_streak = o_max;
                x_max = 0;
                o_max = 0;
            }
            else
            {
                cur_lead = Blank;
                x_max = 0;
                o_max = 0;
            }
        }

        cout<<"Lead after horizontal check: "<<cur_lead<<endl;

        // Search vertically
        j = 0; // Column
        for(i = 0;i < (int)board.size(); i++)
        {
            // Count streaks
            if(board[i][j] == X)
                x_max++;
            else if(board[i][j] == O)
                o_max++;

            // End of the column
            if(i == (int)board.size()-1)
            {
                cout<<"X: "<<x_max<<endl;
                cout<<"O: "<<o_max<<endl;
                // Update column if it's inbounds
                if(j < BOARD_COLS)
                    j++;
                
                // Update who is in the lead after each row & reset
                if(x_max > o_max && x_max > lead_streak)
                {
                    cur_lead = X;
                    lead_streak = x_max;
                    x_max = 0;
                    o_max = 0;
                }
                else if(o_max > x_max && o_max > lead_streak)
                {
                    cur_lead = O;
                    lead_streak = o_max;
                    x_max = 0;
                    o_max = 0;
                }
                else
                {
                    cur_lead = Blank;
                    x_max = 0;
                    o_max = 0;
                }
                
            }
        }

        cout<<"Lead after vertical check: "<<cur_lead<<endl;

        return cur_lead;
    }

    // If board is not full, game is not over    
    return Invalid;
}