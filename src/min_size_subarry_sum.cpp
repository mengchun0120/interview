#include <cassert>
#include <iostream>
#include <vector>
#include <utility>

using namespace std;

/*
Given an array of n positive integers and a positive integer s, find the minimal
length of a contiguous subarray of which the sum >= s. If there isn't one,
return 0 instead.
*/

pair<int,int> findMinSubArray(int s, const vector<int>& arr)
{
    int sum = 0, startIdx = 0, minStart = -1, minEnd = -1;
    int sz = arr.size();

    for(int i = 0; i < sz; ++i) {
        sum += arr[i];
        if(sum < s) {
            continue;
        }

        for(; startIdx <= i; ++startIdx) {
            int a = sum - arr[startIdx];
            if(a < s) {
                break;
            }
            sum = a;
        }

        if(minStart == -1 || (i - startIdx < minEnd - minStart)) {
            minStart = startIdx;
            minEnd = i;
        }
    }

    return pair<int,int>(minStart,minEnd);
}

void test(const vector<int>& arr, int s, const pair<int,int>& result,
          int expectedLen)
{
    if(expectedLen > 0) {
        assert(result.first >= 0 && result.second < (int)arr.size() &&
               result.first <= result.second);

        assert(result.second - result.first + 1 == expectedLen);
    } else {
        assert(result.first == -1 && result.second == -1);
        return;
    }

    int sum = 0;
    for(int i = result.first; i <= result.second; ++i) {
        sum += arr[i];
    }

    assert(sum >= s);
}

int main()
{
    vector<int> a1{1,2,3,4,5,2,4};
    int s1 = 1, e1 = 1;
    pair<int,int> r1 = findMinSubArray(s1, a1);

    test(a1, s1, r1, e1);

    int s2 = 9, e2 = 2;
    pair<int,int> r2 = findMinSubArray(s2, a1);

    test(a1, s2, r2, e2);

    int s3 = 11, e3 = 3;
    pair<int,int> r3 = findMinSubArray(s3, a1);

    test(a1, s3, r3, e3);

    int s4 = 100, e4 = 0;
    pair<int,int> r4 = findMinSubArray(s4, a1);

    test(a1, s4, r4, e4);
}
