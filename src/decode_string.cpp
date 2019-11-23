/*
Given an encoded string, return its decoded string. The enconding rule is:
k[encoded_string], where the encoded_string inside the square brackets is being
repeated exactly k times. Note that k is guaranteed to be a positive integer.
You may assume that the input string is always valid; no extra white spaces,
square brackets are will-formed. etc. Futhermore, you may assume that the
original data doesn't contain any digits and that digits are only for those
repeat numbers, k. For example, there won't be input like 3a or 2[4].
Example: s="3[a]2[bc]", return "aaabcbc".
*/

#include <cassert>
#include <iostream>
#include <string>
#include <list>
#include <sstream>

using namespace std;

string decodeString(const string& s)
{
    ostringstream oss;
    int sz = static_cast<int>(s.size());
    int i = 0;

    while(i < sz) {
        int numStart = i;
        for(; i < sz; ++i) {
            if(s[i] < '0' || s[i] > '9')
                break;
        }

        string numStr = s.substr(numStart, i-numStart);
        int num = stoi(numStr);

        int strStart = i+1;
        for(++i; i < sz; ++i) {
            if(s[i] == ']')
                break;
        }

        string str = s.substr(strStart, i-strStart);
        for(int j = 0; j < num; ++j) {
            oss << str;
        }
        ++i;
    }

    return oss.str();
}

int main()
{
    string s1("2[a]3[bc]");
    string r1 = decodeString(s1);
    assert(r1 == "aabcbcbc");
}
