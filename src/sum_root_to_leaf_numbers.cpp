/*
Given a binary tree containing digits from 0-9 only, each root-to-leaf path
could represent a number.

An example is the root-to-leaf path 1->2->3 which represents the number 123.

Find the total sum of all root-to-leaf numbers.
*/

#include <cassert>
#include <iostream>
#include <list>

using namespace std;

struct Node {
    int digit;
    Node *left, *right;

    Node(int d)
    : digit(d)
    , left(nullptr)
    , right(nullptr)
    {}
};

int getNumber(const list<Node*>& s)
{
    int num = 0;
    for(auto it = s.begin(); it != s.end(); ++it) {
        num = num * 10 + (*it)->digit;
    }
    return num;
}

int getSum(Node *root)
{
    int sum = 0;
    list<Node*> stack;
    Node *n = root;

    while(n) {
        stack.push_back(n);
        if(n->left) {
            n = n->left;
        } else {
            n = n->right;
        }
    }

    while(stack.size() > 0) {
        n = stack.back();

        if(!n->left && !n->right) {
            int num = getNumber(stack);
            sum += num;
        }

        stack.pop_back();
        if(stack.size() == 0)
            break;

        if(stack.back()->left == n && stack.back()->right) {
            n = stack.back()->right;
            while(n) {
                stack.push_back(n);
                if(n->left) {
                    n = n->left;
                } else {
                    n = n->right;
                }
            }
        }
    }

    return sum;
}

int main()
{
    /*
            1
           / \
          2   3
         / \   \
        4   5   6
    */
    Node n1(1);
    Node n2(2);
    Node n3(3);
    Node n4(4);
    Node n5(5);
    Node n6(6);
    n1.left = &n2;
    n1.right = &n3;
    n2.left = &n4;
    n2.right = &n5;
    n3.right = &n6;
    int sum = getSum(&n1);
    assert(sum == 124 + 125 + 136);
}