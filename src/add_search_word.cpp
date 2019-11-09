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
#include <vector>
#include <unordered_set>

using namespace std;

struct Record {
    bool visited;
    unordered_set<int> nextIndices;
};

class WordLib {
public:
    WordLib()
    {}

    ~WordLib()
    {}

    void addWord(const string& word);

    bool search(const string& word);

private:
    static const unsigned int NUM_LETTERS;

private:
    list<vector<Record>> lib;
};

const unsigned int WordLib::NUM_LETTERS = 'z' - 'a' + 1;

void WordLib::addWord(const string& word)
{
    if(lib.size() < word.size()) {
        unsigned int k = word.size() - lib.size();
        for(unsigned int i = 0; i < k; ++i) {
            lib.emplace_back(NUM_LETTERS);
        }
    }

    auto it = lib.begin();
    unsigned int i;

    for(i = 0; i < word.size() - 1; ++i) {
        Record& r = (*it)[i];
        r.nextIndices.insert(word[i] - 'a');
        ++it;
    }

    Record& r = (*it)[i];
    r.nextIndices.insert(-1);
}

bool WordLib::search(const string& word)
{
    unordered_set<int> links1, links2;
    unordered_set<int>* p;
    unsigned int i;
    auto it = lib.begin();

    p = &links1;
    i = 0;
    if(word.size() > 1) {
        if(word[0] != '0') {
            int idx = word[0] - 'a';
            Record& r = (*it)[idx];
            r.
        }
    }
}

int main()
{
}
