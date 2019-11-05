/*
Given a string, determining if it is a palindrome, considering only alphanumberic
characters and ignoring cases.

Note: For the purpose of this problem, we define empty string as valid
palindrome.
*/

#include <cassert>
#include <iostream>
#include <string>

using namespace std;

bool isAlphaNumber(char ch)
{
    return (ch >= 'a' && ch <= 'z') ||
           (ch >= 'A' && ch <= 'Z') ||
           (ch >= '0' && ch <= '9');
}

bool equalIgnoreCase(char c1, char c2)
{
    if(c1 >= 'A' && c1 <= 'Z')
        c1 = 'a' + (c1 - 'A');

    if(c2 >= 'A' && c2 <= 'Z')
        c2 = 'a' + (c2 - 'A');

    return c1 == c2;
}

bool validPalindrome(const string& s)
{
    int i = 0, j = s.size() - 1;

    while(i < j) {
        for(; i < j; ++i) {
            if(isAlphaNumber(s[i]))
                break;
        }

        if(i == j)
            break;

        for(; i < j; --j) {
            if(isAlphaNumber(s[j]))
                break;
        }

        if(i == j)
            break;

        if(!equalIgnoreCase(s[i], s[j]))
            return false;

        ++i;
        --j;
    }

    return true;
}

int main()
{
    string s1;
    assert(validPalindrome(s1));

    string s2("a b,cDE12    2  1,edC  b A");
    assert(validPalindrome(s2));

    string s3("aAbc   c b b a");
    assert(!validPalindrome(s3));

}
