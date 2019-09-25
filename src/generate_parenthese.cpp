#include <cassert>
#include <string>
#include <list>
#include <vector>
#include <unordered_set>
#include <utility>
#include <iostream>

/*
Given n pairs of parentheses, write a function to generate all combinations of
well-formed parentheses.
*/

using namespace std;

void print(const unordered_set<string>& r)
{
    for(auto it = r.begin(); it != r.end(); ++it) {
        cout << *it << endl;
    }
}

void generateParentheses(unordered_set<string>& parentheses, unsigned int n)
{
    if(n == 0) {
        return;
    }

    vector<list<string>> parenthesesVec(n);

    parenthesesVec[0].emplace_back("()");
    for(unsigned int i = 1; i < n; ++i) {
        list<string>& r = parenthesesVec[i];

        string firstPart = "()";
        auto end2 = parenthesesVec[i-1].end();

        for(auto it = parenthesesVec[i-1].begin(); it != end2; ++it) {
            r.push_back(firstPart + *it);
            r.push_back("(" + *it + ")");
        }

        for(unsigned int j = 0; j < i - 1; ++j) {
            auto end1 = parenthesesVec[j].end();
            end2 = parenthesesVec[i-j-2].end();

            for(auto it = parenthesesVec[j].begin(); it != end1; ++it) {
                firstPart = "(" + *it + ")";
                auto it1 = parenthesesVec[i-j-2].begin();

                for(; it1 != end2; ++it1) {
                    r.push_back(firstPart + *it1);
                }
            }
        }
    }

    parentheses.insert(parenthesesVec[n-1].begin(), parenthesesVec[n-1].end());
}

int main()
{
    unordered_set<string> e1{"()"};
    unordered_set<string> r1;
    generateParentheses(r1, 1);
    assert(e1 == r1);

    unordered_set<string> e2{"()()", "(())"};
    unordered_set<string> r2;
    generateParentheses(r2, 2);
    assert(e2 == r2);

    unordered_set<string> e3{"()()()", "()(())", "(()())", "((()))", "(())()"};
    unordered_set<string> r3;
    generateParentheses(r3, 3);
    assert(e3 == r3);
}

