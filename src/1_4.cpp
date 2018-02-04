#include <cassert>
#include <iostream>
#include <string>
#include <list>

/*
Write a function that given a string would print the 'expanded' version of it.
For example a2[bc2[c]]d would print out abcccbcccd. Note: The number before the
opening and closing square brackets is the multiplier for the characters within
the square brackets.
*/

using namespace std;

struct StackNode {
    StackNode(int r)
    : repetition(r)
    , str()
    {
    }

    int repetition;
    list<char> str;
};

void repeat(list<char>& output, const list<char>& input, int repetition)
{
    for(int i = 0; i < repetition; ++i) {
        list<char> r(input);
        output.splice(output.end(), r);
    }
}

void listToString(string& str, const list<char>& input)
{
    if(!input.empty()) {
        str.resize(input.size());
        list<char>::const_iterator it;
        int i = 0;
        for(it = input.begin(); it != input.end(); ++it, ++i) {
            str[i] = *it;
        }
    } else {
        str = "";
    }
}

void expand(string& output, const string& pattern)
{
    list<StackNode> stack;
    int repStart = -1;

    for(unsigned int i = 0; i < pattern.size(); ++i) {
        if(pattern[i] >= '0' && pattern[i] <= '9') {
            if(repStart == -1) {
                repStart = i;
            }

        } else if(pattern[i] == '[') {
            string repStr = pattern.substr(repStart, i-repStart);
            int rep = stoi(repStr);
            stack.emplace_back(rep);
            repStart = -1;

        } else if(pattern[i] == ']') {
            StackNode& top = stack.back();
            list<char> expansion;

            if(!(top.str.empty())) {
                repeat(expansion, top.str, top.repetition);
            }

            stack.pop_back();

            if(stack.empty()) {
                stack.emplace_back(1);
            }

            StackNode& t = stack.back();
            t.str.splice(t.str.end(), expansion);

        } else {
            if(stack.empty()) {
                stack.emplace_back(1);
            }
            stack.back().str.push_back(pattern[i]);
        }
    }

    if(!stack.empty()) {
        listToString(output, stack.back().str);
    } else {
        output = "";
    }
}

int main(int argc, char* argv[])
{
}

