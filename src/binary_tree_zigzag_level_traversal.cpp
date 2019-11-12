/*
Given a binary tree, return the zigzag level order traversal of its nodes'
values, i.e., from left to right, then from right to left for the next level
and alternate between.

For example, given binary tree
       4
      / \
     9   10
        /  \
       15   7
return [4, 10, 9, 15, 7]
*/

#include <cassert>
#include <iostream>
#include <list>

using namespace std;

struct Node {
    int val;
    Node *left, *right;

    Node(int v)
    : val(v)
    , left(nullptr)
    , right(nullptr)
    {}
};

void getZigzagTraversal(list<int>& result, Node* root)
{
    if(!root)
        return;

    list<Node*> q1, q2;
    list<Node*>* q;
    bool leftToRight = true;
    q = &q1;
    q->push_back(root);

    while(q->size() > 0) {
        list<Node*>* nextq = q == &q1 ? &q2 : &q1;
        if(leftToRight) {
            while(q->size() > 0) {
                Node *n = q->front();
                result.push_back(n->val);
                if(n->left) {
                    nextq->push_back(n->left);
                }
                if(n->right) {
                    nextq->push_back(n->right);
                }
                q->pop_front();
            }
        } else {
            while(q->size() > 0) {
                Node *n = q->back();
                result.push_back(n->val);
                if(n->right) {
                    nextq->push_front(n->right);
                }
                if(n->left) {
                    nextq->push_front(n->left);
                }
                q->pop_back();
            }
        }
        q = nextq;
        leftToRight = !leftToRight;
    }
}

ostream& operator<<(ostream& os, const list<int>& l)
{
    os << '[';
    if(l.size() > 0) {
        auto it = l.begin();
        os << *it;
        for(it++; it != l.end(); ++it) {
            os << ", " << *it;
        }
    }
    os << ']';
    return os;
}

int main()
{
/*
       1
      / \
     2   3
    /    /\
   4    5  6
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
    n3.left = &n5;
    n3.right = &n6;
    list<int> r1;
    getZigzagTraversal(r1, &n1);
    cout << r1 << endl;
}
