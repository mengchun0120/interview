#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

/*
Given an array of non-negative integers, you are initially positioned at the
first index of the array. Each element in the array represents your maximum
jump length at that position. Determine if you are able to reach the last
index.
*/

bool reachEnd(const vector<unsigned int> a)
{
    unsigned int maxIdx = a[0];
    unsigned int endIdx = a.size() - 1;
    unsigned int i = 1, idx;

    for(; maxIdx < endIdx && i <= maxIdx && i <= endIdx; ++i) {
        idx = i + a[i];
        if(idx > maxIdx) {
            maxIdx = idx;
        }
    }

    return maxIdx >= endIdx;
}

int main()
{
    vector<unsigned int> a1{2, 3, 1, 1, 4};
    assert(reachEnd(a1) == true);

    vector<unsigned int> a2{1, 1, 1, 1, 1};
    assert(reachEnd(a2) == true);

    vector<unsigned int> a3{2, 2, 1, 0, 2};
    assert(reachEnd(a3) == false);
}
