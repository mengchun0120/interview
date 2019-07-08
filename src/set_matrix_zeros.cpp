#include <cassert>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

/*
Given a matrix, if an element is 0, set its entire row and column to 0. Do it
in place.
*/

void setMatrixZeros(vector<vector<int>>& matrix)
{
    bool topZero = false, bottomZero = false;
    bool leftZero = false, rightZero = false;
    int rowCount = matrix.size(), colCount = matrix[0].size();
    int row, col;

    for(col = 0; col < colCount; ++col) {
        if(matrix[0][col] == 0) {
            topZero = true;
            break;
        }
    }

    for(col = 0; col < colCount; ++col) {
        if(matrix[rowCount-1][col] == 0) {
            bottomZero = true;
            break;
        }
    }

    for(row = 0; row < rowCount; ++row) {
        if(matrix[row][0] == 0) {
            leftZero = true;
            break;
        }
    }

    for(row = 0; row < rowCount; ++row) {
        if(matrix[row][colCount-1] == 0) {
            rightZero = true;
            break;
        }
    }

    for(row = 1; row < rowCount-1; ++row) {
        for(col = 1; col < colCount-1; ++col) {
            if(matrix[row][col] != 0) {
                continue;
            }

            for(int col1 = col-1; col1 >= 0; --col1) {
                if(matrix[row][col1] == 0) {
                    break;
                }

                matrix[row][col1] = 0;
            }

            for(int row1 = row-1; row1 >= 0; --row1) {
                if(matrix[row1][col] == 0) {
                    break;
                }

                matrix[row1][col] = 0;
            }
        }
    }

    for(col = 1; col < colCount-1; ++col) {
        if(matrix[rowCount-1][col] == 0 || matrix[0][col] == 0) {
            for(row = rowCount-1; row >= 0; --row) {
                matrix[row][col] = 0;
            }
        }
    }

    for(row = 1; row < rowCount-1; ++row) {
        if(matrix[row][colCount-1] == 0 || matrix[row][0] == 0) {
            for(col = colCount-1; col >= 0; --col) {
                matrix[row][col] = 0;
            }
        }
    }

    if(topZero) {
        for(col = 0; col < colCount; ++col) {
            matrix[0][col] = 0;
        }
    }

    if(bottomZero) {
        for(col = 0; col < colCount; ++col) {
            matrix[rowCount-1][col] = 0;
        }
    }

    if(leftZero) {
        for(row = 0; row < rowCount; ++row) {
            matrix[row][0] = 0;
        }
    }

    if(rightZero) {
        for(row = 0; row < rowCount; ++row) {
            matrix[row][colCount-1] = 0;
        }
    }
}

namespace std {

template <typename T>
bool operator==(const vector<T>& a1, const vector<T>& a2)
{
    if(a1.size() != a2.size()) {
        return false;
    }

    for(size_t i = 0; i < a1.size(); ++i) {
        if(a1[i] != a2[i]) {
            return false;
        }
    }

    return true;
}

ostream& operator<<(ostream& os, const vector<vector<int>>& m)
{
    os << '[' << endl;
    for(size_t row = 0; row < m.size(); ++row) {
        size_t colCount = m[row].size();

        os << m[row][0];
        for(size_t col = 1; col < colCount; ++col) {
            os << ',' << m[row][col];
        }
        os << endl;
    }
    os << ']';
    return os;
}

}

int main()
{
    vector<vector<int>> matrix1 = {
        {1, 2, 0, 3},
        {4, 0, 5, 6},
        {7, 8, 9, 1},
        {1, 1, 1, 1}
    };
    vector<vector<int>> result1 = {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {7, 0, 0, 1},
        {1, 0, 0, 1}
    };

    setMatrixZeros(matrix1);
    assert(matrix1 == result1);

    vector<vector<int>> matrix2 = {
        {1, 1, 1, 1, 1, 0},
        {0, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1},
        {1, 1, 1, 0, 1, 1},
        {1, 1, 1, 1, 1, 1},
        {1, 1, 1, 0, 1, 1}
    };
    vector<vector<int>> result2 = {
        {0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0},
        {0, 1, 1, 0, 1, 0},
        {0, 0, 0, 0, 0, 0},
        {0, 1, 1, 0, 1, 0},
        {0, 0, 0, 0, 0, 0}
    };

    setMatrixZeros(matrix2);
    assert(matrix2 == result2);
}
