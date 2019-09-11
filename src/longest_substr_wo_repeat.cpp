#include <cassert>
#include <string>
#include <unordered_map>
#include <unordered_set>

/*
Given a string, find the length of the longest substring without repeating
characters.
 */

using namespace std;

int findLongestSubstrWithoutRepeat(const string& s, int& start)
{
    unordered_map<char,int> lastAppear;
    int maxLen, curMaxStart;
    int sz = static_cast<int>(s.size());

    maxLen = 1;
    start = 0;
    curMaxStart = 0;
    lastAppear[s[0]] = 0;

    for(int i = 1; i < sz; ++i) {
        auto it = lastAppear.find(s[i]);
        if(it != lastAppear.end() && it->second >= curMaxStart) {
            curMaxStart = it->second + 1;
        }
        lastAppear[s[i]] = i;

        int curLen = i - curMaxStart + 1;
        if(curLen > maxLen) {
            maxLen = curLen;
            start = curMaxStart;
        }
    }

    return maxLen;
}

void test(const string& s, int expectedMaxLen)
{
    int maxLen, start;

    maxLen = findLongestSubstrWithoutRepeat(s, start);

    assert(maxLen == expectedMaxLen);

    unordered_set<char> appear;
    int last = start + maxLen;
    int i;

    assert(start >= 0 && last <= static_cast<int>(s.size()));
    
    for(i = start; i < last; ++i) {
        if(appear.find(s[i]) != appear.end()) {
            break;
        }

        appear.insert(s[i]);
    }

    assert(i == last);
}

int main(int argc, char *argv[])
{
    string s1 = "a";
    test(s1, 1);

    string s2 = "abcdefg";
    test(s2, 7);

    string s3 = "abcaaaabcdeftttttsuvwxyzdqa";
    test(s3, 11);
}