/*
Given a linked list, swap every two adjacent nodes and return its head.

Example: Given 1->2->3->4, you should return the list as 2->1->4->3.

Note:
Your algoirthm should use only constant extra space. You may not modify the
values in the list'nodes, only nodes itself may be changed.
*/

#include <cassert>
#include <iostream>

using namespace std;

struct Node {
    int val;
    Node *next;

    Node(int v)
    : val(v)
    , next(nullptr)
    {}
};

Node *swapPair(Node *head)
{
}

int main()
{
}

