/*
Given an Android 3X3 key lock screen and two integers m and n, where 1 <= m
<= n <= 9, count the total number of unlock patterns of the Anroid lock screen,
which consisits of minimum of m keys and maximum n keys.

Rules for a valid pattern:
Each pattern must contain at least m keys and at most n keys.
All the keys must be distinct. If the line connecting two consecutive keys in
the pattern passes through any other keys, the other keys must have previously
selected in the pattern. No jumps through non-selected key is allowed. The
order of keys used matters.

Explanation:
1 2 3
4 5 6
7 8 9

Invalid move: 4 - 1 - 3 - 6, line 1 - 3 passes through key 2 which had not been
selected in the pattern.

Invalid move: 4 - 1 - 9 - 2, line 1 - 9 passes through key 5 which had not been
selected in the pattern.

Valid move: 2 - 4 - 1 - 3 - 6, line 1 - 3 is valid because it passes through
key 2, which had been selected in the pattern.

Valid move: 6 - 5 - 4 - 1 - 9 - 2, line 1 - 9 is valid because it passes
through key 5, which had been selected in the pattern.
*/

#include <cassert>
#include <vector>
#include <string>
#include <list>
#include <iostream>

using namespace std;

struct Direction {
    int rowDist;
    int colDist;
};

bool hasNeighborVisited(int r, int c, const char (*m)[3])
{
    static const Direction directions[] = {
        {-1, -1}, {-1, 0}, {-1, 1},
        {0, -1}, {0, 1}, {1, -1},
        {1, 0}, {1, 1}
    };
    static const int numDirections = sizeof(directions) / sizeof(Direction);

    for(int i = 0; i < numDirections; ++i) {
        int row = r + directions[i].rowDist;
        int col = c + directions[i].colDist;
        if(row < 0 || row >= 3 || col < 0 || col >= 3) {
            continue;
        }
        if(m[row][col] == '1') {
            return true;
        }
    }

    return false;
}

void getNextPatterns(list<string>& p, const string& q)
{
    char m[3][3];

    for(int i = 0; i < 3; ++i) {
        for(int j = 0; j < 3; ++j) {
            m[i][j] = '0';
        }
    }

    for(unsigned int k = 0; k < q.size(); ++k) {
        int d = q[k] - '0' - 1;
        int row = d / 3;
        int col = d % 3;
        m[row][col] = '1';
    }

    for(int i = 0; i < 3; ++i) {
        for(int j = 0; j < 3; ++j) {
            if(m[i][j] == '1') {
                continue;
            }

            if(hasNeighborVisited(i, j, m)) {
                char ch = '1' + i*3 + j;
                p.push_back(q + ch);
            }
        }
    }
}

void getPatterns(list<string>& result, int m, int n)
{
    vector<list<string>> patterns(n);

    list<string>& p0 = patterns[0];
    for(int row = 0; row < 3; ++row) {
        for(int col = 0; col < 3; ++col) {
            char ch = '1' + row*3 + col;
            p0.emplace_back(1, ch);
        }
    }

    for(int j = 1; j < n; ++j) {
        list<string>& p = patterns[j];
        auto it = patterns[j-1].begin();
        auto e = patterns[j-1].end();
        for(; it != e; ++it) {
            getNextPatterns(p, *it);
        }
    }

    for(int i = m; i <= n; ++i) {
        list<string>& p = patterns[i-1];
        for(auto it = p.begin(); it != p.end(); ++it) {
            result.emplace_back(move(*it));
        }
    }
}

void print(const list<string>& s)
{
    for(auto it = s.begin(); it != s.end(); ++it) {
        cout << '"' << *it << "\" ";
    }
    cout << endl;
}

int main()
{
    list<string> r1;
    getPatterns(r1, 1, 1);
    print(r1);

    list<string> r2;
    getPatterns(r2, 2, 2);
    print(r2);

    list<string> r3;
    getPatterns(r3, 3, 3);
    print(r3);

    list<string> r4;
    getPatterns(r4, 4, 4);
    print(r4);
}
