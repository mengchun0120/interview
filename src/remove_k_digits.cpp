/*
Given a non-negative integer num represented as a string, remove k digits from
the number so that the new number is the smallest possible.

Note:
The length of num is less than 10002 and will be >= k. The given num doesn't
contain any leading zero.

Example 1:
Input num = "1432219", k=3, Output "1219"

Example 2:
Input num = "10", k=2, Output "0"
*/

#include <cassert>
#include <string>
#include <iostream>

using namespace std;

unsigned int minIdx(const string& s, unsigned int start, unsigned int end)
{
    unsigned int m = start;
    for(unsigned int i = start + 1; i <= end; ++i) {
        if(s[i] < s[m]) {
            m = i;
        }
    }
    return m;
}

void removeDigits(string& result, const string& s, unsigned int k)
{
    if(s.size() <= k) {
        result = "0";
        return;
    }

    unsigned int sz = s.size() - k;
    unsigned int start = 0;

    result.reserve(sz);
    for(unsigned int i = 0; i < sz; ++i) {
        unsigned int end = s.size() - sz + i;
        unsigned int m = minIdx(s, start, end);
        result += s[m];
        start = m + 1;
    }
}

int main()
{
    string s1 = "1432219";
    string r1;
    string e1 = "1219";
    removeDigits(r1, s1, 3);
    assert(e1 == r1);

    string s2 = "214487382";
    string r2;
    string e2 = "1382";
    removeDigits(r2, s2, 5);
    assert(e2 == r2);
}
