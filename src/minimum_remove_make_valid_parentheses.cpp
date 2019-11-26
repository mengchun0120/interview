/*
Given a string s of '(' , ')' and lowercase English characters. 

Your task is to remove the minimum number of parentheses ( '(' or ')', in any positions ) 
so that the resulting parentheses string is valid and return any valid string.

Formally, a parentheses string is valid if and only if:

    It is the empty string, contains only lowercase characters, or
    It can be written as AB (A concatenated with B), where A and B are valid strings, or
    It can be written as (A), where A is a valid string.

Example 1:

Input: s = "lee(t(c)o)de)"
Output: "lee(t(c)o)de"
Explanation: "lee(t(co)de)" , "lee(t(c)ode)" would also be accepted.
*/

#include <cassert>
#include <string>
#include <iostream>
#include <list>

using namespace std;

string minRemoveToMakeValid(const string &s) 
{
    list<int> stack;
    list<int> toRemove;
    int sz = static_cast<int>(s.size());

    for(int i = 0; i < sz; ++i) {
        if(s[i] == '(') {
            stack.push_back(i);
        } else if(s[i] == ')') {
            if(!stack.empty()) {
                stack.pop_back();
            } else {
                toRemove.push_back(i);
            }
        }
    }

    toRemove.splice(toRemove.end(), stack);

    list<char> tmp;
    int i = 0;
    for(auto it1 = toRemove.begin(); it1 != toRemove.end(); ++it1) {
        for(; i < *it1; ++i) {
            tmp.push_back(s[i]);
        }
        ++i;
    }

    for(; i < sz; ++i) {
        tmp.push_back(s[i]);
    }

    return string(tmp.begin(), tmp.end());
}

int main()
{
    string s1 = "l(ee(cod))e)";
    string r1 = minRemoveToMakeValid(s1);
    cout << r1 << endl;

    string s2 = "((((c(ode)anaylisis)aka";
    string r2 = minRemoveToMakeValid(s2);
    cout << r2 << endl;

    string s3 = "a(bc(d)ef)))cde(((abc)";
    string r3 = minRemoveToMakeValid(s3);
    cout << r3 << endl;

    string s4 = "a((((bc(def))a(kad)))fde(((geh)i)j";
    string r4 = minRemoveToMakeValid(s4);
    cout << r4 << endl;
}