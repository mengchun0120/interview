#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

typedef vector<vector<int> > Matrix;

enum Direction {
    RIGHT,
    DOWN,
    LEFT,
    UP
};

void spiralOrder(vector<int>& order, const Matrix& m)
{
    int rowCount = m.size();
    int colCount = m[0].size();
    int orderIdx = 0;
    int rowIdx, colIdx;
    Direction direction = RIGHT;
    int top = 0, bottom = rowCount - 1, left = 0, right = colCount - 1;

    order.resize(rowCount * colCount);
    while(top <= bottom && left <= right) {
        switch(direction) {
        case RIGHT:
            for(rowIdx = top, colIdx = left; colIdx <= right; ++colIdx) {
                order[orderIdx++] = m[rowIdx][colIdx];
            }
            ++top;
            direction = DOWN;
            break;
        case DOWN:
            for(colIdx = right, rowIdx = top; rowIdx <= bottom; ++rowIdx) {
                order[orderIdx++] = m[rowIdx][colIdx];
            }
            --right;
            direction = LEFT;
            break;
        case LEFT:
            for(rowIdx = bottom, colIdx = right; colIdx >= left; --colIdx) {
                order[orderIdx++] = m[rowIdx][colIdx];
            }
            --bottom;
            direction = UP;
            break;
        case UP:
            for(rowIdx = bottom, colIdx = left; rowIdx >= top; --rowIdx) {
                order[orderIdx++] = m[rowIdx][colIdx];
            }
            ++left;
            direction = RIGHT;
            break;
        }
    }
}

namespace std {

template<typename T>
ostream& operator<<(ostream& os, const vector<T>& a)
{
    os << '[';
    size_t sz = a.size();
    if(sz > 0) {
        os << a[0];
        for(size_t i = 1; i < sz; ++i) {
            os << ',' << a[i];
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

void test(int idx, const Matrix& m, const vector<int>& expected)
{
    cout << "Spiral matrix " << idx << endl;

    vector<int> result;

    spiralOrder(result, m);
    cout << result << endl;
    assert(result == expected);
}

int main(int argc, char *argv[])
{
     Matrix m1{
        {1,2},
        {3,4}
     };
     vector<int> expected1{1, 2, 4, 3};

     test(1, m1, expected1);

     Matrix m2{
         {0, 1, 2, 3},
         {11, 12, 13, 4},
         {10, 15, 14, 5},
         {9, 8, 7, 6}
     };
     vector<int> expected2{0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};

     test(2, m2, expected2);
}
