#include <cassert>
#include <iostream>
#include <string>

/*
Give you a pattern (digit in the pattern matches the correspondingnumber of
letters, letter means match the letter itself), a string to determine whether
match: ex:
abc -> 'abc' true
'1oc3' -> 'aoczzz', 'bocabc' true
*/

using namespace std;

bool match(const string& pattern, const string& str)
{
    unsigned int p = 0, s = 0;

    while(p < pattern.size() && s < str.size()) {
        if(pattern[p] >= '0' && pattern[p] <= '9') {
            unsigned int d = static_cast<unsigned int>(pattern[p] - '0');
            s += d;
        } else {
            ++s;
        }
        ++p;
    }

    return (p == pattern.size()) && (s == str.size());
}

int main(int argc, char* argv[])
{
    string p1("");
    string s1("");
    assert(match(p1, s1));
    cout << "test1 successful" << endl;

    string p2("");
    string s2("a");
    assert(!match(p2, s2));
    cout << "test2 successful" << endl;

    string p3("abc");
    string s3("abc");
    assert(match(p3, s3));
    cout << "test3 successful" << endl;

    string p4("abc");
    string s4("abcd");
    assert(!match(p4, s4));
    cout << "test4 successful" << endl;

    string p5("a3b2");
    string s5("acdbbef");
    assert(match(p5, s5));
    cout << "test5 successful" << endl;

    string p6("a3b2");
    string s6("abcdefgh");
    assert(!match(p6, s6));
    cout << "test6 successful" << endl;
}

