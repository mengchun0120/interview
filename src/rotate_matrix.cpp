#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

/*
Rotate an nxn matrix by 90 degrees clockwise.
*/

typedef vector<vector<int>> Matrix;

void rotate(Matrix& m)
{
    unsigned int top = 0, bottom = m.size() - 1;
    unsigned int left = 0, right = m[0].size() - 1;

    while(top < bottom) {
        unsigned int steps = bottom - top;
        for(unsigned int i = 0; i < steps; ++i) {
            int tmp = m[bottom-i][left];
            m[bottom-i][left] = m[bottom][right-i];
            m[bottom][right-i] = m[top+i][right];
            m[top+i][right] = m[top][left+i];
            m[top][left+i] = tmp;
        }

        ++top;
        --bottom;
        ++left;
        --right;
    }
}

namespace std {

template<typename T>
ostream& operator<<(ostream& os, const vector<vector<T>>& a)
{
    os << '[';
    size_t rowCount = a.size();
    if(rowCount > 0) {
        for(size_t row = 0; row < rowCount; ++row) {
            size_t colCount = a[row].size();
            for(size_t col = 1; col < colCount; ++col) {
                os << a[row][col] << ',';
            }
            os << endl;
        }
    }
    os << ']';
    return os;
}

template<typename T>
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

}

int main()
{
    Matrix m1{
        {0, 1, 2, 3},
        {4, 5, 6, 7},
        {8, 9, 10, 11},
        {12, 13, 14, 15}
    };
    Matrix r1{
        {12, 8, 4, 0},
        {13, 9, 5, 1},
        {14, 10, 6, 2},
        {15, 11, 7, 3}
    };

    rotate(m1);
    assert(r1 == m1);
}
