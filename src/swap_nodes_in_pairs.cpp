/*
Given a linked list, swap every two adjacent nodes and return its head.

Example: Given 1->2->3->4, you should return the list as 2->1->4->3.

Note:
Your algoirthm should use only constant extra space. You may not modify the
values in the list'nodes, only nodes itself may be changed.
*/

#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

struct Node {
    int val;
    Node *next;

    Node(int v)
    : val(v)
    , next(nullptr)
    {}
};

void print(Node *head)
{
    Node *n = head;
    while(n) {
        cout << n->val << ' ';
        n = n->next;
    }
    cout << endl;
}

Node *swapPair(Node *head)
{
    Node *first = head;
    Node *pairPrev, *pairFirst;

    pairPrev = nullptr;
    pairFirst = head;
    while(pairFirst) {
        Node *pairSecond = pairFirst->next;

        if(!pairSecond)
            break;

        Node *pairNext = pairSecond->next;

        pairSecond->next = pairFirst;
        pairFirst->next = pairNext;
        if(pairPrev) {
            pairPrev->next = pairSecond;
        } else {
            first = pairSecond;
        }

        pairPrev = pairFirst;
        pairFirst = pairNext;
    }

    return first;
}

Node *initList(const vector<int>& v)
{
    if(v.size() == 0)
        return nullptr;

    Node *first = new Node(v[0]);
    Node *prev = first;

    for(unsigned int i = 1; i < v.size(); ++i) {
        Node *n = new Node(v[i]);
        prev->next = n;
        prev = n;
    }

    return first;
}

int main()
{
    vector<int> v1{1,2,3,4,5,6,7,8};
    Node *head1 = initList(v1);
    Node *r1 = swapPair(head1);
    print(r1);
}

