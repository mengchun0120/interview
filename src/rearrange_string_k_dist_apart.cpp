/*
Given a non-empty string s and an integer k, rearrange the string such that the
same characters are at least distance k from each other.

All input strings are given in lowercase letters. If it is not possible to
rearrange the string, return an empty string "".

Example 1: Input s="aabbcc", k=3, Output "abcabc"

Example 2: Input s="aaabc", k=3, Output ""

Example 3: Input s="aaadbbcc", k=2, Output "abacabcd"
*/

#include <cassert>
#include <string>
#include <iostream>
#include <unordered_map>
#include <algorithm>

using namespace std;

struct Item {
    char ch;
    int count;
    Next *next;

    Item()
    : next(nullptr)
    {}
};

bool compare(const Item& i1, const Item& i2)
{
    return i1.count > i2.count;
}

string rearrange(const string& s, int k)
{
    unordered_map<char,int> charMap;
    for(unsigned int i = 0; i < (int)s.size(); ++i) {
        auto it = charMap.find(s[i]);
        if(it != charMap.end()) {
            ++(it->second);
        } else {
            charMap[s[i]] = 1;
        }
    }

    vector<Item> v(charMap.size());
    int j = 0;
    for(auto it = charMap.begin(); it != charMap.end(); ++it) {
        v[j].ch = it->first;
        v[j].count = it->second;
    }

    sort(v.begin(), v.end(), compare);
    for(j = 0; j < (int)v.size() - 1; ++j) {
        v[j].next = &v[j+1];
    }

    vector<char> r(v.size());

    
}

int main()
{
}
