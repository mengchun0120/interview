#include <cassert>
#include <vector>
#include <string>
#include <list>

/*
Given a 2D board containing 'X' and 'O', capture all regions surrounded by 'X'.
A region is captured by flipping all 'O's into 'X's in that surrounded region.

Example:
XXXX
XOOX
XXOX
XOXX

After running your function, the board should be:
XXXX
XXXX
XXXX
XOXX

Explanation:
Surrounded regions shouldn't be on the border, which means that any 'O' on the
border of the board are not flipped to 'X'. Any 'O' that is not on the border
and it is not connected to an 'O' on the border will be flipped to 'X'. Two
cells are connected if they are adjacent cells connected horizontally or
vertically.
*/

using namespace std;

struct Pos {
    unsigned int row;
    unsigned int col;

    Pos(unsigned int r, unsigned int c)
    : row(r)
    , col(c)
    {}
};

void flipRegions(vector<string>& board)
{
    unsigned int rowCount = board.size();
    unsigned int colCount = board[0].size();
    unsigned int row, col;
    list<Pos> queue;

    for(col = 0; col < colCount; ++col) {
        if(board[0][col] == 'O') {
            board[0][col] = 'U';
            queue.emplace_back(0, col);
        }
        if(board[rowCount-1][col] == 'O') {
            board[rowCount-1][col] = 'U';
            queue.emplace_back(rowCount-1, col);
        }
    }

    for(row = 1; row < rowCount-1; ++row) {
        if(board[row][0] == 'O') {
            board[row][0] = 'U';
            queue.emplace_back(row, 0);
        }
        if(board[row][colCount-1] == 'O') {
            board[row][colCount-1] = 'U';
            queue.emplace_back(row, colCount-1);
        }
    }

    while(queue.size() > 0) {
        Pos& p = queue.front();
        if(p.row > 0 && board[p.row-1][p.col] == 'O') {
            board[p.row-1][p.col] = 'U';
            queue.emplace_back(p.row-1, p.col);
        }
        if(p.row < rowCount - 1 && board[p.row+1][p.col] == 'O') {
            board[p.row+1][p.col] = 'U';
            queue.emplace_back(p.row+1, p.col);
        }
        if(p.col > 0 && board[p.row][p.col-1] == 'O') {
            board[p.row][p.col-1] = 'U';
            queue.emplace_back(p.row, p.col-1);
        }
        if(p.col < colCount - 1 && board[p.row][p.col+1] == 'O') {
            board[p.row][p.col+1] = 'U';
            queue.emplace_back(p.row, p.col+1);
        }
        queue.pop_front();
    }

    for(row = 0; row < rowCount; ++row) {
        for(col = 0; col < colCount; ++col) {
            if(board[row][col] == 'U') {
                board[row][col] = 'O';
            } else if(board[row][col] == 'O') {
                board[row][col] = 'X';
            }
        }
    }
}

int main()
{
    vector<string> t1{
        "XXXX",
        "XOOX",
        "XXOX",
        "XOXX"
    };
    vector<string> e1{
        "XXXX",
        "XXXX",
        "XXXX",
        "XOXX"
    };
    flipRegions(t1);
    assert(t1 == e1);

    vector<string> t2{
        "XXOOXX",
        "XXOXXX",
        "XOOXOX",
        "XXXOOX",
        "XOXXXX"
    };
    vector<string> e2{
        "XXOOXX",
        "XXOXXX",
        "XOOXXX",
        "XXXXXX",
        "XOXXXX"
    };
    flipRegions(t2);
    assert(t2 == e2);
}
