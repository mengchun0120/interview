#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

/*
Given an array of size n, find the majority element. The majority element is the
element that appears more than n/2 times. You may assume that the array is
non-empty and the majority element always exists in the array.
*/

int findMajority(const vector<int>& a)
{
    int majority = a[0];
    int count = 1;

    for(size_t i = 1; i < a.size(); ++i) {
        if(count == 0) {
            majority = a[i];
            count = 1;
        } else if(a[i] == majority) {
            ++count;
        } else {
            --count;
        }
    }

    return majority;
}

int main()
{
    vector<int> a1{1, 2, 3, 4, 4, 3, 3, 3, 3};
    assert(3 == findMajority(a1));

    vector<int> a2{2, 3, 2, 3, 4, 3, 3, 2, 2, 3, 3};
    assert(3 == findMajority(a2));
}
