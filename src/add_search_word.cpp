/*
Design a data structure that supports the following two operations:

void addWord(word)
bool search(word)

search(word) can search a literal word or regular expression string containing
only letters and .. A . means it can represent any one letter.

Note: you may assume that all words consist of lowercase letters a-z.
*/

#include <cassert>
#include <string>
#include <list>
#include <iostream>
#include <unordered_set>
#include <unordered_map>

using namespace std;

struct Record {
    bool hasEnd;
    unordered_set<char> next;

    Record()
    : hasEnd(false)
    {}
};

typedef unordered_map<char, Record> RecordMap;

class WordLib {
public:
    WordLib()
    {}

    ~WordLib()
    {}

    void add(const string& word);

    bool search(const string& word);

private:
    list<RecordMap> lib;
};

void WordLib::add(const string& word)
{
    if(lib.size() < word.size()) {
        unsigned int k = word.size() - lib.size();
        for(unsigned int i = 0; i < k; ++i) {
            lib.emplace_back();
        }
    }

    auto libIt = lib.begin();
    unsigned int i;

    for(i = 0; i < word.size() - 1; ++i, ++libIt) {
        Record& r = (*libIt)[word[i]];
        r.next.insert(word[i+1]);
    }

    Record& e = (*libIt)[word[i]];
    e.hasEnd = true;
}

bool WordLib::search(const string& word)
{
    if(word.size() > lib.size())
        return false;

    unordered_set<char> match1, match2;
    unordered_set<char> *p = &match1;
    auto libIt = lib.begin();
    unsigned int i;

    if(word[0] != '.') {
        auto it = libIt->find(word[0]);
        if(it == libIt->end())
            return false;

        Record& r = it->second;
        if(word.size() == 1)
            return r.hasEnd;

        p->insert(r.next.begin(), r.next.end());
    } else {
        if(word.size() == 1) {
            for(auto it = libIt->begin(); it != libIt->end(); ++it) {
                Record& r = it->second;
                if(r.hasEnd)
                    return true;
            }
            return false;
        }

        for(auto it = libIt->begin(); it != libIt->end(); ++it) {
            Record& r = it->second;
            p->insert(r.next.begin(), r.next.end());
        }
    }

    ++libIt;
    for(i = 1; i < word.size() - 1; ++i, ++libIt) {
        unordered_set<char> *n = (p == &match1) ? &match2 : &match1;
        n->clear();
        if(word[i] != '.') {
            auto it = p->find(word[i]);
            if(it == p->end())
                return false;

            Record& r = (*libIt)[word[i]];
            n->insert(r.next.begin(), r.next.end());
        } else {
            for(auto it = p->begin(); it != p->end(); ++it) {
                Record& r = (*libIt)[*it];
                n->insert(r.next.begin(), r.next.end());
            }
        }
        p = n;
    }

    if(word[i] != '.') {
        auto it = p->find(word[i]);
        if(it == p->end())
            return false;

        Record& r = (*libIt)[word[i]];
        return r.hasEnd;
    }

    for(auto it = p->begin(); it != p->end(); ++it) {
        Record& r = (*libIt)[*it];
        if(r.hasEnd)
            return true;
    }
    return false;
}

int main()
{
    WordLib lib;
    lib.add("a");
    assert(lib.search("a"));
    assert(lib.search("."));

    lib.add("abc");
    lib.add("abd");
    lib.add("cast");
    lib.add("word");
    lib.add("will");
    lib.add("wors");
    assert(!lib.search("ab"));
    assert(!lib.search("acd"));
    assert(lib.search("wors"));
    assert(lib.search(".or."));
    assert(lib.search("..."));
}
