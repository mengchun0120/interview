#include <cassert>
#include <iostream>
#include <string>
#include <list>

/*
Find valid bracket from provided string. Only { [ ( are involved as str.
A valid bracket contains with a enclose companion.
Example: {} is valid, [[] Invalid
Input: {[()]}[]() Result: Valid
Input: {}[]()( Result: Invalid
*/

using namespace std;

bool isLeftBracket(char c)
{
    return c == '[' || c == '(' || c == '{';
}

bool isRightBracket(char c)
{
    return c == ']' || c == ')' || c == '}';
}

bool isMatchingBracket(char leftBracket, char c)
{
    switch(leftBracket) {
    case '[':
        return c == ']';
    case '{':
        return c == '}';
    case '(':
        return c == ')';
    }
    return false;
}

bool checkBracket(const string& str)
{
    list<char> stack;
    for(unsigned int i = 0; i < str.size(); ++i) {
        if(isLeftBracket(str[i])) {
            stack.push_back(str[i]);
        } else if(isRightBracket(str[i])) {
            if(stack.empty() || !isMatchingBracket(stack.back(), str[i])) {
                return false;
            }

            stack.pop_back();
        }
    }
    return stack.empty();
}

void test(int testIndex, const string& str, bool expected)
{
    bool ret = checkBracket(str);
    assert(ret == expected);
    cout << "test" << testIndex << " successful" << endl;
}

int main(int argc, char* argv[])
{
    cout << "Running 1_12 ..." << endl;

    int testIndex = 1;
    test(testIndex++, "{}", true);
    test(testIndex++, "[[]", false);
    test(testIndex++, "{()[(){[]}]}", true);
    test(testIndex++, "[[[{{{{", false);
    test(testIndex++, "[[(()))))))]]]", false);
}

