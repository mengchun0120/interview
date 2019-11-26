/*
Given a list of words, each word consists of English lowercase letters.

Let's say word1 is a predecessor of word2 if and only if we can add exactly 
one letter anywhere in word1 to make it equal to word2.  For example, "abc"
is a predecessor of "abac".

A word chain is a sequence of words [word_1, word_2, ..., word_k] with k >= 1,
where word_1 is a predecessor of word_2, word_2 is a predecessor of word_3, and 
so on.

Return the longest possible length of a word chain with words chosen from the 
given list of words.

Example 1:

Input: ["a","b","ba","bca","bda","bdca"]
Output: 4
Explanation: one of the longest word chain is "a","ba","bda","bdca".

    1 <= words.length <= 1000
    1 <= words[i].length <= 16
    words[i] only consists of English lowercase letters.
*/

#include <cassert>
#include <string>
#include <iostream>
#include <vector>
#include <list>

using namespace std;

struct Node {
    string *str;
    int maxLen;

    Node(string *s, int len)
    : str(s)
    , maxLen(len)
    {}
};

bool isOneStepAway(const string &s1, const string &s2)
{
    int i;
    int sz1 = static_cast<int>(s1.size());
    
    for(i = 0; i < sz1; ++i) {
        if(s1[i] != s2[i])
            break;
    }

    for(; i < sz1; ++i) {
        if(s1[i] != s2[i+1])
            return false;
    }

    return true;
}

int longestStringChain(vector<string>& words)
{
    int maxLen = 0;
    int sz = static_cast<int>(words.size());
    for(int i = 0; i < sz; ++i) {
        if(static_cast<int>(words[i].size()) > maxLen) {
            maxLen = words[i].size();
        }
    }

    vector<list<string*>> indexedWords(maxLen+1);
    for(int i = 0; i < sz; ++i) {
        indexedWords[words[i].size()].emplace_back(&words[i]);
    }

    list<Node> prevWords1, prevWords2;
    list<Node>* prev = &prevWords1;
    int maxChain = 0;

    for(int len = 0; len <= maxLen; ++len) {
        list<Node>* p = (prev == &prevWords1) ? &prevWords2 : &prevWords1;
        p->clear();

        auto end1 = indexedWords[len].end();
        for(auto it1 = indexedWords[len].begin(); it1 != end1; it1++) {
            int max1 = 1;

            for(auto it2 = prev->begin(); it2 != prev->end(); ++it2) {
                if(isOneStepAway(*(it2->str), **it1) && (it2->maxLen + 1) > max1) {
                    max1 = it2->maxLen + 1;
                }
            }

            p->emplace_back(*it1, max1);
            if(max1 > maxChain) {
                maxChain = max1;
            }
        }

        prev = p;
    }

    return maxChain;
}

int main()
{
    vector<string> words1{"a", "ab"};
    assert(2 == longestStringChain(words1));

    vector<string> words2{"a", "acc", "acd", "ac", "bd", "cd", "acde"};
    assert(4 == longestStringChain(words2));
}