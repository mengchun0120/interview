#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

/*
A robot is moving in a matrix. It starts at the top left corner, and tries to
move to the bottom left corner. It can only more right or down. How many unique
paths there exist?
*/

int uniquePaths(int rowCount, int colCount)
{
    vector<vector<int>> m;
    int i, j;

    m.resize(rowCount);
    for(i = 0; i < rowCount; ++i) {
        m[i].resize(colCount);
    }

    for(i = 0; i < colCount; ++i) {
        m[0][i] = 1;
    }

    for(i = 1; i < rowCount; ++i) {
        m[i][0] = 1;
    }

    for(i = 1; i < rowCount; ++i) {
        for(j = 1; j < colCount; ++j) {
            m[i][j] = m[i][j-1] + m[i-1][j];
        }
    }

    return m[rowCount-1][colCount-1];
}

int main(int argc, char *argv[])
{
    assert(uniquePaths(2,2) == 2);
    assert(uniquePaths(3,3) == 6);
}
