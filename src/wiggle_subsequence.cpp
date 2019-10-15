/*
A sequence of numbers is called a wiggle sequence if the difference between
successive numbers strictlly alternate between positive and negative. The first
difference (if one exists) may be either positive or negative. A sequence with
fewer than two elements is trivially a wiggle sequence.

For example, [1, 7, 4, 9, 2, 5] is a wiggle sequence because the differences
(6, -3, 5, -7, 3) are alternately positive and negative. In contrast, [1, 4, 7,
2, 5] and [1, 7, 4, 5, 5] are not wiggle sequences, the first because its first
two differences are positive, and the second because its last difference is
zero.

Given a sequence of integers, return the length of the longest subsequence that
is a wiggle sequence. A subsequence is obtained by deleting some number of
elements (eventually, also zero) from the original sequence, leaving the
remaining elements in their original order.

Example 1:
Input: [1, 7, 4, 9, 2, 5]
Output: 6

Explanation: The entire sequence is a wiggle sequence.

Example 2:
Input: [1, 17, 5, 10, 13, 15, 10, 5, 16, 8]
Output: 7

Explanation: There are several subsequences that achieve this length. One is
[1, 17, 10, 13, 10, 16, 8].

Example 3:
Input: [1, 2, 3, 4, 5, 6, 7, 8, 9]
Output: 2

Follow up:
Can you do it in O(n) time?
*/

#include <cassert>
#include <vector>
#include <iostream>

using namespace std;

void longestWiggle(vector<int>& r, const vector<int>& a)
{
    if(a.size() == 0) {
        return;
    }

    unsigned int sz = a.size();
    unsigned int i;

    r.push_back(a[0]);

    for(i = 1; i < sz; ++i) {
        if(a[i] != a[0]) {
            break;
        }
    }

    if(i == sz) {
        return;
    }

    bool isPositive = a[i] > a[0];

    r.push_back(a[i]);
    for(; i < sz; ++i) {
        if(a[i] == a[i-1]) {
            continue;
        }

        bool newPositive = a[i] > a[i-1];
        if(newPositive != isPositive) {
            r.push_back(a[i]);
        } else {
            r.back() = a[i];
        }

        isPositive = newPositive;
    }
}

bool isWiggle(const vector<int>& r)
{
    if(r.size() <= 1) {
        return true;
    }

    if(r[0] == r[1]) {
        return false;
    }

    bool isPositive = r[1] > r[0];
    unsigned int sz = r.size();

    for(unsigned int i = 2; i < sz; ++i) {
        if(r[i] == r[i-1]) {
            return false;
        }

        bool newPositive = r[i] > r[i-1];
        if(newPositive == isPositive) {
            return false;
        }

        isPositive = newPositive;
    }

    return true;
}

bool isSubArray(const vector<int>& r, const vector<int>& a)
{
    unsigned int sz1 = r.size();
    unsigned int sz2 = a.size();
    unsigned int i1 = 0, i2 = 0;

    while(i1 < sz1 && i2 < sz2) {
        if(r[i1] == a[i2]) {
            ++i1;
        }
        ++i2;
    }

    return i1 == sz1;
}

bool checkWiggle(const vector<int>& r, const vector<int>& a)
{
    return isWiggle(r) && isSubArray(r, a);
}

void print(const vector<int>& r)
{
    cout << '[';
    if(r.size() > 0) {
        unsigned int sz = r.size();
        cout << r[0];
        for(unsigned int i = 1; i < sz; ++i) {
            cout << ", " << r[i];
        }
    }
    cout << ']';
}

int main()
{
    vector<int> a1{1};
    vector<int> r1;
    longestWiggle(r1, a1);
    assert(r1.size() == 1 && checkWiggle(r1, a1));

    vector<int> a2{1, 1, 2, 2, 3, 3};
    vector<int> r2;
    longestWiggle(r2, a2);
    assert(r2.size() == 2 && checkWiggle(r2, a2));

    vector<int> a3{1, 17, 5, 10, 13, 15, 10, 5, 16, 8};
    vector<int> r3;
    longestWiggle(r3, a3);
    assert(r3.size() == 7 && checkWiggle(r3, a3));
}
