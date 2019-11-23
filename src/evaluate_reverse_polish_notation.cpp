/*
Evaluate the value of an arithmetic expression in Reverse Polish Notation. Valid
operators are +, -, *, /. Each operand may be an integer or another expression.
Division between two integers should truncate toward zero. The given RPN
expression is always valid. That means the expression would always evaluate to
a result and there won't be any divide by zero operation.
*/

#include <cassert>
#include <list>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

int evaluate(const vector<string>& expr)
{
    list<int> stack;
    int sz = static_cast<int>(expr.size());

    for(int i = 0; i < sz; ++i) {
        if(expr[i] == "+") {
            int a2 = stack.back();
            stack.pop_back();
            int a1 = stack.back();
            stack.pop_back();
            int r = a1 + a2;
            stack.push_back(r);
        } else if(expr[i] == "-") {
            int a2 = stack.back();
            stack.pop_back();
            int a1 = stack.back();
            stack.pop_back();
            int r = a1 - a2;
            stack.push_back(r);
        } else if(expr[i] == "*") {
            int a2 = stack.back();
            stack.pop_back();
            int a1 = stack.back();
            stack.pop_back();
            int r = a1 * a2;
            stack.push_back(r);
        } else if(expr[i] == "/") {
            int a2 = stack.back();
            stack.pop_back();
            int a1 = stack.back();
            stack.pop_back();
            int r = a1 / a2;
            stack.push_back(r);
        } else {
            int t = stoi(expr[i]);
            stack.push_back(t);
        }
    }

    return stack.back();
}

int main()
{
    vector<string> ex1{"12", "13", "+"};
    assert(25 == evaluate(ex1));

    vector<string> ex2{"4", "2", "3", "-", "*"};
    assert(-4 == evaluate(ex2));

    vector<string> ex3{"4", "5", "7", "-", "20", "*", "+"};
    assert(-36 == evaluate(ex3));
}
