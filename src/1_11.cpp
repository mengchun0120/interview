#include <cassert>
#include <iostream>
#include <string>
#include <unordered_set>

/*
There is a dictionary already implemented. Write a method , which takes input
String without space, to replace the characters from the strings which are not
present in dictionary with –
Example: Dictionary – a*
.............Input- aaabaa
.............Output- aaa_aa
*/

using namespace std;

void replace(string& str, const unordered_set<char>& dict)
{
    for(unsigned int i = 0; i < str.size(); ++i) {
        auto it = dict.find(str[i]);
        if(it == dict.end()) {
            str[i] = '_';
        }
    }
}

void test(int testIndex, const string& str, const unordered_set<char>& dict,
          const string& expected)
{
    string s = str;
    replace(s, dict);
    assert(s == expected);
    cout << "test" << testIndex << " successful" << endl;
}

int main(int argc, char* argv[])
{
    cout << "Running 1_11 ..." << endl;

    int testIndex = 1;
    unordered_set<char> d1;
    test(testIndex++, "abacde", d1, "______");

    d1.insert('a');
    test(testIndex++, "aaaaaa", d1, "aaaaaa");
    test(testIndex++, "ababba", d1, "a_a__a");

    d1.insert('b');
    test(testIndex++, "ababab", d1, "ababab");
    test(testIndex++, "abcabc", d1, "ab_ab_");
}

