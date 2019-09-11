#include <cassert>
#include <string>
#include <iostream>

/*
Given a string s, find the longest palindromic substring in s. You may assume
that the maximum length of s is 1000.
*/

using namespace std;

void extendSubstr(const string& s, int left, int right, int& start, int& end)
{
    int l, r;
    int sz = static_cast<int>(s.size());

    for(l = left, r = right; l >= 0 && r < sz; --l, ++r) {
        if(s[l] != s[r]) {
            break;
        }
    }

    start = l + 1;
    end = r - 1;
}

void findLongestPalindromicSubstr(const string& s, int& start, int& end)
{
    int start1, end1, len;
    int maxLen = -1;
    int sz = static_cast<int>(s.size());

    for(int i = 0; i < sz; ++i) {
        extendSubstr(s, i - 1, i + 1, start1, end1);
        len = end1 - start1 + 1;
        if(len > maxLen) {
            start = start1;
            end = end1;
            maxLen = len;
        }

        extendSubstr(s, i, i + 1, start1, end1);
        len = end1 - start1 + 1;
        if(len > maxLen) {
            start = start1;
            end = end1;
            maxLen = len;
        }
    }
}

void test(const string& s, int expectedLen)
{
    int start, end;
    int sz = static_cast<int>(s.size());

    findLongestPalindromicSubstr(s, start, end);

    assert(0 <= start);
    assert(start <= end);
    assert(end < sz);
    assert(end - start + 1 == expectedLen);

    cout << s.substr(start, end - start + 1) << endl;

    int l, r;

    for(l = start, r = end; l < r; ++l, --r) {
        if(s[l] != s[r]) {
            break;
        }
    }

    assert(l >= r);
}

int main(int argc, char *argv[])
{
    string s1 = "a";
    test(s1, 1);

    string s2 = "aa";
    test(s2, 2);

    string s3 = "aaaaabccbabbbbbb";
    test(s3, 6);

    string s4 = "abccbadbccbdaccccaaaa";
    test(s4, 8);
}