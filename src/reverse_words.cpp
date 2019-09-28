#include <cassert>
#include <string>
#include <iostream>

/*
Given an input string, reverse the string word by word. For example, given
s = "the sky is blue", return "blue is sky the".
*/

using namespace std;

void reverse(string& s, int start, int end)
{
    char tmp;
    for(int i = start, j = end; i < j; ++i, --j) {
        tmp = s[i];
        s[i] = s[j];
        s[j] = tmp;
    }
}

void reverseWords(string& s)
{
    int sz = s.size();
    reverse(s, 0, sz-1);
    
    int start = 0, end;

    while(start < sz) {
        while(start < sz && s[start] == ' ') {
            ++start;
        }

        end = start;
        while(end < sz && s[end] != ' ') {
            ++end;
        }

        reverse(s, start, end-1);
        start = end;
    }
}

int main()
{
    string s1 = "the sky is blue";
    string e1 = "blue is sky the";
    reverseWords(s1);
    assert(s1 == e1);
}