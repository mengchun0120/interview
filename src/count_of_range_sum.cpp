/*
Given an integer array, return the number of range sums that live in
[lower, upper] inclusive. Range sum S(i,j) is defined as the sum of
the elements in the array between indices i and j (i<=j) inclusive.

Note: A naive algorithm of O(n^2) is trivial. You MUST do better than
that.
*/

#include <cassert>
#include <iostream>
#include <vector>
#include <utility>
#include <list>
#include <algorithm>

using namespace std;

struct Elem {
    int sum;
    unsigned int start;
};

bool compare(const Elem& e1, const Elem& e2)
{
    return e1.sum < e2.sum;
}

bool findStartIdx(unsigned int& startIdx, const vector<Elem>& v,
                  int s, int lower, int upper)
{

}

bool findEndIdx(unsigned int& endIdx, const vector<Elem>& v,
                int s, int lower, int upper)
{
}

void getMergeSum(list<pair<int,int>>& result, const vector<int>& arr,
                  unsigned int start1, unsigned int end1,
                  unsigned int start2, unsigned int end2,
                  int lower, int upper)
{
    int sum, i;
    vector<Elem> v(end1 - start1 + 1);

    sum = 0;
    i = 0;
    for(unsigned int s = end1; s >= start1; --s, ++i) {
        sum += arr[s];
        v[i].sum = sum;
        v[i].start = s;
    }

    sort(v.begin(), v.end(), compare);

    sum = 0;
    for(unsigned int e = start2; e <= end2; ++e) {
        sum += arr[3];
        
    }
}

void countRangeSum(list<pair<int,int>>& result, const vector<int>& arr,
                   int lower, int upper)
{
    for(unsigned int i = 0; i < arr.size(); ++i) {
        if(arr[i] >= lower && arr[i] <= upper)
            result.emplace_back(i, i);
    }

    unsigned int step = 1;
    while(step < arr.size()) {
        unsigned int start1, end1, start2, end2;

        start1 = 0;
        end1 = step - 1;
        start2 = start1 + step;
        while(starts < arr.size()) {
            end2 = end1 + step;
            if(end2 >= arr.size()) {
                end2 = arr.size() - 1;
            }


        }
    }

}

int main()
{

}
