/*
There are a row of n houses, each house can be painted with one of the k colors.
The cose of painting each house with a certain color is different. You have to
paint all the houses such that no two adjacent houses have the same color.

The cost of painting the house with a certain color is represented by a nxk cost
matrix. For example, costs[0][0] is the cost of painting house 0 with color 0;
cost[1][2] is the cost of painting house 1 with color 2, and so on... Find the
minimum cost to paint all houses.

Note:
All costs are positive integers.

Could you solve it in O(nk) runtime?
*/

#include <cassert>
#include <vector>
#include <iostream>

using namespace std;

struct Elem {
    int minCost;
    int prevColor;
};

void print(const vector<int>& r)
{
    for(auto it = r.begin(); it != r.end(); ++it) {
        cout << *it << ' ';
    }
    cout << endl;
}

void print(const vector<Elem>& r)
{
    for(auto it = r.begin(); it != r.end(); ++it) {
        cout << it->minCost << ':' << it->prevColor << ' ';
    }
    cout << endl;
}

void findMinimumTwo(int *result, const vector<Elem>& p)
{
    if(p[0].minCost < p[1].minCost) {
        result[0] = 0;
        result[1] = 1;
    } else {
        result[0] = 1;
        result[1] = 0;
    }

    for(unsigned int i = 2; i < p.size(); ++i) {
        int cost = p[i].minCost;
        if(cost >= p[result[1]].minCost) {
            continue;
        }

        if(cost >= p[result[0]].minCost) {
            result[1] = i;
        } else {
            result[1] = result[0];
            result[0] = i;
        }
    }
}

void fillCost(vector<Elem>& cur, const vector<Elem>& prev,
              const vector<int>& cost, const int* minTwo)
{
    int numColors = static_cast<int>(cur.size());
    for(int color = 0; color < numColors; ++color) {
        if(color != minTwo[0]) {
            cur[color].minCost = prev[minTwo[0]].minCost + cost[color];
            cur[color].prevColor = minTwo[0];
        } else {
            cur[color].minCost = prev[minTwo[1]].minCost + cost[color];
            cur[color].prevColor = minTwo[1];
        }
    }
}

int getMinPaints(vector<int>& paints, const vector<vector<Elem>>& records)
{
    int minCost, minColor;
    const vector<Elem>& p = records.back();
    int numColors = static_cast<int>(records[0].size());

    minCost = p[0].minCost;
    minColor = 0;
    for(int color = 1; color < numColors; ++color) {
        if(p[color].minCost < minCost) {
            minCost = p[color].minCost;
            minColor = color;
        }
    }

    int numHouses = static_cast<int>(records.size());
    int curColor, j;

    paints.resize(numHouses);
    paints[numHouses-1] = minColor;

    curColor = minColor;
    j = numHouses - 2;
    for(int h = numHouses - 1; h > 0; --h, --j) {
        curColor = records[h][curColor].prevColor;
        paints[j] = curColor;
    }

    return minCost;
}

int findMinCost(vector<int>& paints, const vector<vector<int>>& costs)
{
    unsigned int numHouses = costs.size();
    unsigned int numColors = costs[0].size();
    vector<vector<Elem>> records(numHouses);
    unsigned int house, color;

    for(house = 0; house < numHouses; ++house) {
        records[house].resize(numColors);
    }

    for(color = 0; color < numColors; ++color) {
        records[0][color].minCost = costs[0][color];
        records[0][color].prevColor = -1;
    }

    for(house = 1; house < numHouses; ++house) {
        vector<Elem>& prev = records[house-1];
        vector<Elem>& cur = records[house];
        const vector<int>& c = costs[house];

        int minTwo[2];

        findMinimumTwo(minTwo, prev);
        fillCost(cur, prev, c, minTwo);
    }

    return getMinPaints(paints, records);
}

bool checkResult(const vector<int> paints, const vector<vector<int>>& costs,
                 int expected)
{
    if(paints.size() != costs.size()) {
        cerr << "paints has wrong size" << endl;
        return false;
    }

    int cost = 0;
    int numColors = static_cast<int>(costs[0].size());

    for(unsigned int i = 0; i < paints.size(); ++i) {
        if(paints[i] < 0 || paints[i] >= numColors) {
            cerr << "paints[" << i << "] has wrong color" << endl;
            return false;
        }

        if(i > 0 && paints[i] == paints[i-1]) {
            cerr << "paints[" << i << "] has same color as paints[" << (i-1)
                 << "]" << endl;
            return false;
        }

        cost += costs[i][paints[i]];
    }

    if(cost != expected) {
        cerr << "total cost is wrong" << endl;
        return false;
    }

    return true;
}

int main()
{
    vector<vector<int>> costs1{
        {9, 8},
        {2, 3}
    };
    vector<int> paints1;
    int r1 = findMinCost(paints1, costs1);
    int e1 = 10;
    assert(r1 == e1 && checkResult(paints1, costs1, e1));

    vector<vector<int>> costs2{
        {2, 3, 5},
        {4, 7, 8},
        {9, 2, 6}
    };
    vector<int> paints2;
    int r2 = findMinCost(paints2, costs2);
    int e2 = 9;
    assert(r2 == e2 && checkResult(paints2, costs2, e2));

    vector<vector<int>> costs3{
        {6, 9, 10},
        {8, 2, 11},
        {6, 11, 3},
        {1, 3, 2},
        {1, 9, 10}
    };
    vector<int> paints3;
    int r3 = findMinCost(paints3, costs3);
    int e3 = 15;
    assert(r3 == e3 && checkResult(paints3, costs3, e3));
}

