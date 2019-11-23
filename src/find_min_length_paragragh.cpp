#include <cassert>
#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <unordered_set>
#include <unordered_map>

using namespace std;

/*
You are given with a large paragraph and N words. You have to find a min
length subparagraph of the paragraph which contain all those N words in any
order. Here length of a paragraph is the count of words in the paragraph.
*/

struct WordRecord {
    WordRecord(unsigned int i)
    : idx(i)
    , nextDup(nullptr)
    {}

    unsigned int idx;
    WordRecord *nextDup;
};

void convertToSet(const vector<string>& wordVector,
                  unordered_set<string>& wordSet)
{
    for(unsigned int i = 0; i < wordVector.size(); ++i) {
        if(wordSet.find(wordVector[i]) == wordSet.end()) {
            wordSet.insert(wordVector[i]);
        }
    }
}

bool findMinSubparagraph(const vector<string>& paragraph,
                         const vector<string>& dictionary,
                         unsigned int& start, unsigned int& end)
{
    if(paragraph.empty()) {
        return false;
    }

    unordered_set<string> wordSet;
    convertToSet(dictionary, wordSet);

    list<WordRecord> wordList;
    unordered_map<string, WordRecord*> foundWords;
    unsigned i;

    for(i = 0; i < paragraph.size(); ++i) {
        if(wordSet.find(paragraph[i]) == wordSet.end()) {
            continue;
        }

        wordList.emplace_back(i);

        WordRecord* rec = &(wordList.back());
        auto it = foundWords.find(paragraph[i]);

        if(it == foundWords.end()) {
            foundWords[paragraph[i]] = rec;
        } else {
            it->second->nextDup = rec;
            it->second = rec;
        }

        if(foundWords.size() == wordSet.size()) {
            break;
        }
    }

    if(foundWords.size() != wordSet.size()) {
        return false;
    }

    start = wordList.front().idx;
    end = wordList.back().idx;
    unsigned int minLen = end - start + 1;

    if(minLen == wordSet.size()) {
        return true;
    }

    for(i = end + 1; i < paragraph.size(); ++i) {
        if(wordSet.find(paragraph[i]) == wordSet.end()) {
            continue;
        }

        wordList.emplace_back(i);

        WordRecord* rec = &(wordList.back());
        auto it = foundWords.find(paragraph[i]);

        it->second->nextDup = rec;
        it->second = rec;

        while(wordList.front().nextDup != nullptr) {
            wordList.pop_front();
        }

        unsigned int newLen = wordList.back().idx - wordList.front().idx + 1;
        if(newLen < minLen) {
            start = wordList.front().idx;
            end = wordList.back().idx;
            minLen = newLen;

            if(minLen == wordSet.size()) {
                return true;
            }
        }
    }

    return true;
}

void test(const vector<string>& paragraph,
          const vector<string>& dictionary,
          bool found, unsigned int minLen)
{
    unsigned int start, end;
    bool result = findMinSubparagraph(paragraph, dictionary, start, end);

    assert(result == found);

    if(!found) {
        return;
    }

    assert(0 <= start && start < paragraph.size());
    assert(start <= end && end < paragraph.size());
    assert(end-start+1 == minLen);

    unordered_set<string> wordSet, foundWords;
    convertToSet(dictionary, wordSet);

    for(unsigned int i = start; i <= end; ++i) {
        if(wordSet.find(paragraph[i]) == wordSet.end()) {
            continue;
        }

        if(foundWords.find(paragraph[i]) == foundWords.end()) {
            foundWords.insert(paragraph[i]);
        }
    }

    assert(foundWords.size() == wordSet.size());
}

int main(int argc, char* argv[])
{
    vector<string> p1{};
    vector<string> d1{"a"};
    test(p1, d1, false, 0);
    cout << "test1 successful" << endl;

    vector<string> p2{"aa"};
    vector<string> d2{"aa"};
    test(p2, d2, true, 1);
    cout << "test2 successful" << endl;

    vector<string> p3{"bb", "aa", "dd"};
    vector<string> d3{"aa", "cc"};
    test(p3, d3, false, 0);
    cout << "test3 successful" << endl;

    vector<string> p4{"aa", "dd", "cc", "cc", "aa"};
    vector<string> d4{"aa", "cc"};
    test(p4, d4, true, 2);
    cout << "test4 successful" << endl;
}
