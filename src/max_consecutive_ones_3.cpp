/*
Given an array A of 0s and 1s, we may change up to K values from 0 to 1.

Return the length of the longest (contiguous) subarray that contains only 1s. 
*/

#include <cassert>
#include <iostream>
#include <vector>
#include <list>

using namespace std;

int longestOnes(vector<int>& A, int K)
{
    list<int> flipPositions;
    int maxLen = 0;
    int lastStart = -1;
    int sz = static_cast<int>(A.size());

    for(int i = 0; i < sz; ++i) {
        if(A[i] == 1) {
            if(lastStart == -1) {
                lastStart = i;
            }
        } else if(K > 0) {
            if(static_cast<int>(flipPositions.size()) < K) {
                A[i] = 1;
                flipPositions.emplace_back(i);
                if(i == 0 || A[i-1] == 0) {
                    lastStart = i;
                }
            } else {
                int len = i - lastStart;
                if(len > maxLen) {
                    maxLen = len;
                }

                int first = flipPositions.front();
                A[first] = 0;
                lastStart = first + 1;
                flipPositions.pop_front();
                A[i] = 1;
                flipPositions.emplace_back(i);
            }
        } else {
            if(lastStart != -1) {
                int len = i - lastStart;
                if(len > maxLen) {
                    maxLen = len;
                }
                lastStart = -1;
            }
        }
    }

    if(sz > 0 && A[sz-1] == 1) {
        int len = sz - lastStart;
        if(len > maxLen) {
            maxLen = len;
        }
    }

    return maxLen;
}

int main()
{
    vector<int> A1{1, 0, 0, 0, 1, 1, 0};
    assert(4 == longestOnes(A1, 2));

    vector<int> A2{1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0};
    assert(12 == longestOnes(A2, 3));

    vector<int> A3{0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1};
    assert(7 == longestOnes(A3, 2));
}