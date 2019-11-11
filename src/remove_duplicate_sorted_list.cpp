/*
Given a sorted linked list, delete all nodes that have duplicate numbers,
leaving only distinct numbers from the original list.
*/

#include <cassert>
#include <vector>
#include <iostream>

using namespace std;

struct Node {
    int val;
    Node *next;

    Node(int i)
    : val(i)
    , next(nullptr)
    {}
};

void removeDuplicate(Node *head)
{
    if(!head)
        return;

    Node *prev = head;
    Node *cur = head->next;

    while(cur) {
        if(prev->val == cur->val) {
            prev->next = cur->next;
            delete cur;
            cur = prev->next;
        } else {
            prev = cur;
            cur = cur->next;
        }
    }
}

Node *getLinkedList(const vector<int>& v)
{
    if(v.size() == 0)
        return nullptr;

    Node *head = new Node(v[0]);
    Node *prev = head;

    for(unsigned int i = 1; i < v.size(); ++i) {
        Node *n = new Node(v[i]);
        prev->next = n;
        prev = n;
    }

    return head;
}

bool compareLinkedList(Node *h1, Node *h2)
{
    Node *n1 = h1;
    Node *n2 = h2;

    while(n1 && n2) {
        if(n1->val != n2->val) {
            return false;
        }
        n1 = n1->next;
        n2 = n2->next;
    }

    return !n1 && !n2;
}

int main()
{
    vector<int> l1{1,2,2,2,3,3,4,5,6,6,6};
    vector<int> e1{1,2,3,4,5,6};
    Node *h1 = getLinkedList(l1);
    removeDuplicate(h1);
    Node *f1 = getLinkedList(e1);
    assert(compareLinkedList(h1, f1));
}
