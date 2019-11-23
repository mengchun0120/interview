/*
Given a linked list, reverse the nodes of a linked list k at a time and return
its modified list. k is a positive integer and is less than or equal to the
length of the linked list. If the number of nodes is not a multiple of k then
left-out nodes in the end should remain as it is.

Example: Given this linked list: 1->2->3->4->5, for k=2, you should return
2->1->4->3->5; for k=3, you should return 3->2->1->4->5

Note: Only constant extra memory is allowed. You may not alter the values in the
list's nodes, only nodes itself may be changed.
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

Node *reverseGroup(Node *head, int k)
{
    if(!head || k < 2)
        return head;

    Node *first = head;
    Node *groupPrev, *groupFirst;

    groupPrev = nullptr;
    groupFirst = head;
    while(groupFirst) {
        Node *groupEnd = groupFirst->next;
        for(int i = 2; i < k && groupEnd; ++i) {
            groupEnd = groupEnd->next;
        }

        if(!groupEnd)
            break;

        Node *groupNext = groupEnd->next;

        Node *prev = groupFirst;
        Node *n = prev->next;
        while(true) {
            Node *next = n->next;
            n->next = prev;
            if(n == groupEnd)
                break;
            prev = n;
            n = next;
        }

        groupFirst->next = groupNext;
        if(groupPrev) {
            groupPrev->next = groupEnd;
        } else {
            first = groupEnd;
        }

        groupPrev = groupFirst;
        groupFirst = groupNext;
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
    Node *r1 = reverseGroup(head1, 3);
    print(r1);
}
