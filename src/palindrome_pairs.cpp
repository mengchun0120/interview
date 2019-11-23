/*
Given a list of unique words, find all pairs of distinct indices (i,j) in the
given list, so that the concatenation of the two words, i.e., words[i]+words[j]
is a palindrome.

Example 1: Input ["abcd","dcba","lls","s","sssll"],
Output [[0,1],[1,0],[3,2],[2,4]]
*/

#include <cassert>
#include <iostream>
#include <string>
#include <list>
#include <utility>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

bool isPalindrome(const string& s, int start, int end)
{
    int i = start, j = end;
    for(; i < j; ++i, --j) {
        if(s[i] != s[j])
            return false;
    }
    return true;
}

string getReverseSubstr(const string& s, int start, int end)
{
    vector<char> v(end-start+1);
    int i, j;

    for(i = end, j = 0; i >= start; --i, ++j) {
        v[j] = s[i];
    }

    return string(v.begin(), v.end());
}

void findPalindromePairs(list<pair<int,int>>& pairs,
                         const vector<string>& words)
{
    unordered_map<string,int> wordMap;
    int wordCount = static_cast<int>(words.size());

    for(int i = 0; i < wordCount; ++i) {
        wordMap[words[i]] = i;
    }

    for(int i = 0; i < wordCount; ++i) {
        int wordSize = static_cast<int>(words[i].size());
        for(int j = 0; j < wordSize - 1; ++j) {
            if(isPalindrome(words[i], 0, j)) {
                string s = getReverseSubstr(words[i], j+1, wordSize-1);
                auto it = wordMap.find(s);
                if(it != wordMap.end() && it->second != j) {
                    pairs.emplace_back(it->second, j);
                }
            }
        }

        for(int j = wordSize - 1; j > 0; --j) {
            if(isPalindrome(words[i], j, wordSize - 1)) {
                string s = getReverseSubstr(words[i], 0, j-1);
                auto it = wordMap.find(s);
                if(it != wordMap.end() && it->second != j) {
                    pairs.emplace_back(j, it->second);
                }
            }
        }

        string s = getReverseSubstr(words[i], 0, wordSize-1);
        auto it = wordMap.find(s);
        if(it != wordMap.end() && it->second != i) {
            pairs.emplace_back(i, it->second);
        }
    }
}

void findPalindromePairs2(list<pair<int,int>>& pairs,
                          const vector<string>& words)
{
    int wordCount = static_cast<int>(words.size());
    unordered_map<string, int> wordMap;

    for(int i = 0; i < wordCount; ++i) {
        wordMap[words[i]] = i;
    }

    for(int i = 0; i < wordCount; ++i) {
        for(int j = 0; j < wordCount; ++j) {
            if(i == j)
                continue;
            string s = words[i] + words[j];
            pair<int,int> p(i, j);
            if(isPalindrome(s, 0, s.size()-1) &&
               find(pairs.begin(), pairs.end(), p) != pairs.end()) {
                pairs.push_back(p);
            }
        }
    }
}

bool test(const vector<string>& v)
{
    list<pair<int,int>> r1, r2;
    findPalindromePairs(r1, v);
    findPalindromePairs2(r2, v);

    if(r1.size() != r2.size())
        return false;

    for(auto it2 = r2.begin(); it2 != r2.end(); ++it2) {
        auto it1 = r1.begin();
        for(; it1 != r1.end(); ++it1) {
            if(*it1 == *it2)
                break;
        }
        if(it1 == r1.end())
            return false;
    }

    return true;
}

int main()
{
    vector<string> words{"abc", "cba", "lls", "sll", "s", "slll"};
    assert(test);
}
