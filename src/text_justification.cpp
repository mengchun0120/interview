#include <cassert>
#include <string>
#include <list>
#include <vector>
#include <utility>
#include <iostream>

/*
Given an array of words and a length L, format the text such that each line has
exactly L characters and is fully (left and right) justified.

You should pack your words in a greedy approach; that is, pack as many words as
you can in each line. Pad extra spaces ' ' when necessary so that each line has
exactly L characters.

Extra spaces between words should be distributed as evenly as possible. If the
number of spaces on a line don't divide evenly between words, the empty slots on
the left will be assigned more spaces than the slots on the right.

For the last line of text, it should be left justified and no extra space is
inserted between words.
*/

using namespace std;

void print(const vector<string>& lines)
{
    for(unsigned int i = 0; i < lines.size(); ++i) {
        cout << "'" << lines[i] << "'" << endl;
    }
}

string mergeLineEven(const vector<string>& words, unsigned int start, 
                     unsigned int end, unsigned int lineLen)
{
    unsigned int len = 0, i;
    for(i = start; i <= end; ++i) {
        len += words[i].size();
    }

    unsigned int numSlots = end - start;
    unsigned int firstGap, remainGap;
    
    if(numSlots > 0) {
        remainGap = (lineLen - len) / numSlots;
        firstGap = lineLen - len - remainGap * (numSlots - 1);
    } else {
        firstGap = lineLen - len;
    }

    string s;
    s += words[start];
    s.insert(s.end(), firstGap, ' ');

    for(i = start + 1; i < end; ++i) {
        s += words[i];
        s.insert(s.end(), remainGap, ' ');
    }

    if(numSlots > 1) {
        s += words[end];
    }

    return s;
}

string mergeLastLine(const vector<string>& words, unsigned int start)
{
    string s;

    s += words[start];
    for(unsigned int i = start + 1; i < words.size(); ++i) {
        s += ' ';
        s += words[i];
    }

    return s;
}

void justify(vector<string>& result, const vector<string>& words,
             unsigned int lineLen)
{
    if(words.size() == 0) {
        return;
    }

    unsigned int i = 0;
    
    while(true) {
        unsigned int len = words[i].size();
        unsigned int j = i + 1;
        for(; j < words.size(); ++j) {
            unsigned int newLen = len + words[j].size() + 1;
            if(newLen > lineLen) {
                break;
            }
            len = newLen;
        }

        if(j < words.size()) {
            result.push_back(move(mergeLineEven(words, i, j-1, lineLen)));
            i = j;
        } else {
            result.push_back(move(mergeLastLine(words, i)));
            break;
        }
    }
}

int main()
{
    vector<string> words1{"This", "is", "an", "example", "of", "text",
                          "justification"};
    vector<string> r1;
    vector<string> e1{
        "This    is    an",
        "example  of text",
        "justification"
    };

    justify(r1, words1, 16);
    assert(r1 == e1);
}