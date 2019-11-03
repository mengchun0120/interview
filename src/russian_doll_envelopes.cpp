/*
You have a number of envelopes with widths and heights given as a pair of
integers (w, h). One envelope can fit into another if and only if both the
width and height of one envelope is greater than the width and height of the
other envelope. What is the maximum number of envelope can you Russian doll?
(put one inside other)

Example:
Input: [[5,4],[6,4],[6,7],[2,3]]
Output: 3
*/

#include <cassert>
#include <vector>
#include <iostream>
#include <utility>
#include <algorithm>

using namespace std;

ostream& operator<<(ostream& os, const pair<int,int>& p)
{
    os << '(' << p.first << ',' << p.second << ')';
    return os;
}

ostream& operator<<(ostream& os, const vector<pair<int,int>>& s)
{
    os << '[';
    if(s.size() > 0) {
        os << s[0];
        for(unsigned int i = 1; i < s.size(); ++i) {
            os << ", " << s[i];
        }
    }
    os << ']';
    return os;
}

bool compare(const pair<int,int>& p1, const pair<int,int>& p2)
{
    if(p1.first != p2.first)
        return p1.first < p2.first;

    return p1.second < p2.second;
}

void getMaxRussianDoll(vector<pair<int,int>>& result,
                       const vector<pair<int,int>>& envelopes)
{
    vector<pair<int,int>> copy(envelopes);
    sort(copy.begin(), copy.end(), compare);
}

int main()
{
    vector<pair<int,int>> p1{{9,10},{2,1},{1,2},{3,4},{3,2}};
}
