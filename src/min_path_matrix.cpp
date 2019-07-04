#include <cassert>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
Given a matrix of non-positive integers, find the path from top left to right
bottom which minimizes the sum of all its numbers along its path. Note that
you can only move right or down.
*/

int findMinPath(const vector<vector<int>>& m)
{
    int rowCount = m.size(), colCount = m[0].size();
    vector<vector<int>> t(rowCount);
    int i, j;

    for(i = 0; i < colCount; ++i) {
        t[i].resize(colCount);
    }

    t[0][0] = m[0][0];

    for(i = 1; i < colCount; ++i) {
        t[0][i] = t[0][i-1] + m[0][i];
    }

    for(i = 1; i < rowCount; ++i) {
        t[i][0] = t[i-1][0] + m[i][0];
    }

    for(i = 1; i < rowCount; ++i) {
        for(j = 1; j < colCount; ++j) {
            t[i][j] = min(t[i-1][j], t[i][j-1]) + m[i][j];
        }
    }

    return t[rowCount-1][colCount-1];
}

int main()
{
    vector<vector<int>> m1{
        {0, 1, 2},
        {7, 8, 3},
        {6, 5, 4}
    };

    assert(findMinPath(m1) == 10);
}
