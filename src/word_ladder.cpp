#include <cassert>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <list>
#include <utility>

using namespace std;

/*
Given two words (beginWord and endWord), and a dictionary's word list, find the
length of shortest transformation sequence from beginWord to endWord, such that

* Only one letter can be changed at a time.
* Each transformed word must exist in the word list. Note that beginWord is not
a transformed word.

Note:
Return 0 if there is no such transformation sequence.
All words have the same length.
All words contain only lowercase alphabetic characters.
You may assume no duplicates in the word list.
You may assume beginWord and endWord are non-empty and are not the same.
*/

bool moveOneStep(list<string>& frontier,
                 unordered_set<string>& unvisited,
                 const string& word,
                 const string& target)
{
    for(size_t i = 0; i < word.size(); ++i) {
        for(char ch = 'a'; ch <= 'z'; ++ch) {
            if(ch != word[i]) {
                string tmp(word);
                tmp[i] = ch;

                if(tmp == target) {
                    return true;
                }

                auto it = unvisited.find(tmp);
                if(it != unvisited.end()) {
                    frontier.push_back(tmp);
                    unvisited.erase(it);
                }
            }
        }
    }

    return false;
}

int ladderLength(const string& beginWord, const string& endWord,
                 const vector<string>& wordList)
{
    unordered_set<string> unvisited;
    list<string> frontier;

    for(auto it = wordList.begin(); it != wordList.end(); ++it) {
        unvisited.insert(*it);
    }

    int len = 1;

    if(moveOneStep(frontier, unvisited, beginWord, endWord)) {
        return len;
    }

    while(frontier.size() > 0 && unvisited.size() > 0) {
        ++len;

        list<string> nextFrontier;
        for(auto it = frontier.begin(); it != frontier.end(); ++it) {
            if(moveOneStep(nextFrontier, unvisited, *it, endWord)) {
                return len;
            }
        }

        frontier = move(nextFrontier);
    }

    return 0;
}

int main()
{
    vector<string> wordList1{
        "hot", "dot", "dog", "lot", "log", "cog"
    };
    string beginWord1 = "hit";
    string endWord1 = "cog";

    assert(4 == ladderLength(beginWord1, endWord1, wordList1));

    string beginWord2 = "zis";

    assert(0 == ladderLength(beginWord2, endWord1, wordList1));
}

