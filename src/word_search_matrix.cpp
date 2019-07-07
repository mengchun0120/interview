#include <cassert>
#include <vector>
#include <string>
#include <list>
#include <iostream>

using namespace std;

/*
Given a 2D board and a word, find if the word exists in the grid. The word can
be constructed from letters of sequentially adjacent cell, where "adjacent"
cells are those horizontally or vertically neighboring. The same letter cell
may not be used more than once.
*/

enum Direction {
    NONE,
    UP,
    RIGHT,
    DOWN,
    LEFT
};

struct Node {
    size_t m_row, m_col;
    Direction m_direct;

    Node(size_t row, size_t col, Direction direct);
};

Node::Node(size_t row, size_t col, Direction direct)
: m_row(row)
, m_col(col)
, m_direct(direct)
{
}

ostream& operator<<(ostream& os, const Node& n)
{
    os << '(' << n.m_row << ',' << n.m_col << ',' << (int)n.m_direct << ')';
    return os;
}

template <typename T>
ostream& operator<<(ostream& os, const list<T>& l)
{
    os << '[';
    if(l.size() > 0) {
        auto it = l.begin();
        os << *it;
        for(++it; it != l.end(); ++it) {
            os << ',' << *it;
        }
    }
    os << ']';
    return os;
}

bool exists(const list<Node>& trace, size_t row, size_t col)
{
    for(auto it = trace.begin(); it != trace.end(); ++it) {
        if(it->m_row == row && it->m_col == col) {
            return true;
        }
    }

    return false;
}

bool findWord(const vector<vector<char>>& board, const string& s)
{
    list<Node> trace;
    size_t row = 0, col = 0;
    size_t rowCount = board.size(), colCount = board[0].size();

    while(row < rowCount && col < colCount && trace.size() < s.size()) {
        if(trace.size() > 0) {
            Node& last = trace.back();
            if(last.m_direct == LEFT) {
                trace.pop_back();
            } else {
                size_t r = last.m_row, c = last.m_col;
                switch(last.m_direct) {
                case NONE:
                    --r;
                    last.m_direct = UP;
                    break;
                case UP:
                    ++c;
                    last.m_direct = RIGHT;
                    break;
                case RIGHT:
                    ++r;
                    last.m_direct = DOWN;
                    break;
                case DOWN:
                    --c;
                    last.m_direct = LEFT;
                    break;
                }

                if(r >= 0 && r < rowCount && c >= 0 && c < colCount) {
                    if(!exists(trace, r, c) &&
                       board[r][c] == s[trace.size()]) {
                        trace.emplace_back(r, c, NONE);
                    }
                }
            }
        } else {
            if(board[row][col] == s[0]) {
                trace.emplace_back(row, col, NONE);
            } else {
                ++col;
                if(col == colCount) {
                    ++row;
                    col = 0;
                }
            }
        }
    }

    return trace.size() == s.size();
}

int main()
{
    vector<vector<char>> board1 = {
        {'a', 'c', 'd', 'e'},
        {'s', 'e', 'a', 't'},
        {'d', 'e', 's', 'e'},
        {'f', 'g', 'h', 'i'}
    };
    string word1 = "acde";
    string word2 = "zsk";
    string word3 = "acdeteihgf";

    assert(findWord(board1, word1) == true);
    assert(findWord(board1, word2) == false);
    assert(findWord(board1, word3) == true);

}

