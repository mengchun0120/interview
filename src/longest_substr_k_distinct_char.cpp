/*
Given a string, find the length of the longest substring T that contains at
most k distinct characters.

Example 1: Input s="eceba", k=2, Output 3
Explanation: T is "ece"

Example 2: s="aa", k=1 Output 2
Explanation: T is "aa"
*/

#include <cassert>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <iostream>

using namespace std;

struct Elem {
    char ch;
    int count;

    Elem(char c, int cc)
    : ch(c)
    , count(cc)
    {}
};

void findCounts(vector<Elem>& counts, const string& s)
{
    unordered_map<char,int> map;
    unsigned int sz = s.size();

    for(unsigned int i = 0; i < sz; ++i) {
        auto it = map.find(s[i]);
        if(it == map.end()) {
            map[s[i]] = 1;
        } else {
            (it->second)++;
        }
    }

    counts.reserve(map.size());
    for(auto it = map.begin(); it != map.end(); ++it) {
        counts.emplace_back(it->first, it->second);
    }
}

bool compare(const Elem& e1, const Elem& e2)
{
    return e1.count > e2.count;
}

void getChars(unordered_set<char>& chars, const string& s, unsigned int k)
{
    vector<Elem> counts;

    findCounts(counts, s);
    sort(counts.begin(), counts.end(), compare);

    unsigned int c = counts.size();
    if(c > k) {
        c = k;
    }

    for(unsigned int i = 0; i < c; ++i) {
        chars.insert(counts[i].ch);
    }
}

string findSubstr(const string& s, unsigned int k)
{
    unordered_set<char> chars;

    getChars(chars, s, k);

    unsigned int sz = s.size();
    string r;

    for(unsigned int i = 0; i < sz; ++i) {
        if(chars.find(s[i]) != chars.end()) {
            r += s[i];
        }
    }

    return r;
}

bool isSubstr(const string& s1, const string& s2)
{
    unsigned int i1, i2;
    unsigned int sz1 = s1.size();
    unsigned int sz2 = s2.size();

    i1 = 0;
    i2 = 0;
    while(i1 < sz1 && i2 < sz2) {
        if(s1[i1] == s2[i2]) {
            ++i1;
        }
        ++i2;
    }

    return i1 == sz1;
}

int main()
{
    string s1 = "ecebad";
    string r1 = findSubstr(s1, 3);
    assert(r1.size() == 4 && isSubstr(r1, s1));

    string s2 = "aaaaaaaaa";
    string r2 = findSubstr(s2, 2);
    assert(r2.size() == 9 && isSubstr(r2, s2));

    string s3 = "abcdefghijkeeeeeeeeeeebbbbbb";
    string r3 = findSubstr(s3, 4);
    assert(r3.size() == 21 && isSubstr(r3, s3));
}
