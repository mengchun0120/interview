/*
On a 2 dimensional grid with R rows and C columns, we start at (r0, c0) facing east.

Here, the north-west corner of the grid is at the first row and column, and the south-east corner of the grid is at the last row and column.

Now, we walk in a clockwise spiral shape to visit every position in this grid. 

Whenever we would move outside the boundary of the grid, we continue our walk outside the grid (but may return to the grid boundary later.) 

Eventually, we reach all R * C spaces of the grid.

Return a list of coordinates representing the positions of the grid in the order they were visited.
*/

#include <cassert>
#include <vector>
#include <iostream>

using namespace std;

void spiralMatrix3(vector<vector<int>>& positions, int R, int C, int r0, int c0)
{
    int top = r0, bottom = r0, left = c0, right = c0;
    int r = r0, c = c0;
    int count = 0, total = R * C;
    int direction = 0;

    positions.resize(total);
    positions[0].resize(2);
    positions[0][0] = r;
    positions[0][1] = c;
    ++c;
    ++count;
    while(count < total) {
        switch(direction) {
            case 0: { // east
                ++right;
                if(r < 0 || r >= R || c >= C || right < 0) {
                    c = right;
                } else {
                    if(c < 0) {
                        c = 0;
                    }

                    int bound = right < C ? right : C - 1;
                    for(; c <= bound; ++c) {
                        positions[count].resize(2);
                        positions[count][0] = r;
                        positions[count][1] = c;
                        ++count;
                    }
                    c = right;
                }
            }
            r++;
            break;
            case 1: { // south
                ++bottom;
                if(c < 0 || c >= C || r >= R || bottom < 0) {
                    r = bottom;
                } else {
                    if(r < 0) {
                        r = 0;
                    }

                    int bound = bottom < R ? bottom : R - 1;
                    for(; r <= bound; ++r) {
                        positions[count].resize(2);
                        positions[count][0] = r;
                        positions[count][1] = c;
                        ++count;
                    }
                    r = bottom;
                }
            }
            c--;
            break;
            case 2: { // west
                --left;
                if(r < 0 || r >= R || c < 0 || left >= C) {
                    c = left;
                } else {
                    if(c >= C) {
                        c = C - 1;
                    }

                    int bound = left >= 0 ? left : 0;
                    for(; c >= bound; --c) {
                        positions[count].resize(2);
                        positions[count][0] = r;
                        positions[count][1] = c;
                        ++count;
                    }
                    c = left;
                }
            }
            r--;
            break;
            case 3: { // north
                --top;
                if(c < 0 || c >= C || r < 0 || top >= R) {
                    r = top;
                } else {
                    if(r >= R) {
                        r = R - 1;
                    }

                    int bound = top >= 0 ? top : 0;
                    for(; r >= bound; --r) {
                        positions[count].resize(2);
                        positions[count][0] = r;
                        positions[count][1] = c;
                        ++count;
                    }
                    r = top;
                }
            }
            c++;
            break;
        }
        direction = (direction + 1) % 4;
    }
}

ostream& operator<<(ostream& os, const vector<vector<int>> positions)
{
    if(positions.size() == 0)
        return os;

    os << '(' << positions[0][0] << ',' << positions[0][1] << ')';
    for(int i = 1; i < (int)positions.size(); ++i) {
        os << ", (" << positions[i][0] << ',' << positions[i][1] << ')';
    }

    return os;
}

int main()
{
    vector<vector<int>> p1;
    spiralMatrix3(p1, 1, 4, 0, 0);
    cout << p1 << endl;

    vector<vector<int>> p2;
    spiralMatrix3(p2, 4, 4, 1, 1);
    cout << p2 << endl;

    vector<vector<int>> p3;
    spiralMatrix3(p3, 4, 4, 0, 3);
    cout << p3 << endl;
}
