/*
Given a linked list and a value x, partition  it such that all nodes less than
x come before nodes greater than or equal to x.

You should preserve the original relative order of the nodes in each of the two
partitions.
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

Node* partitionList(Node *head, int x)
{
    Node *firstHead = nullptr;
    Node *firstLast = nullptr;
    Node *secondHead = nullptr;
    Node *secondLast = nullptr;
    Node *n;

    n = head;
    while(n) {
        if(n->val < x) {
            if(firstLast) {
                firstLast->next = n;
            } else {
                firstHead = n;
            }
            firstLast = n;
        } else {
            if(secondLast) {
                secondLast->next = n;
            } else {
                secondHead = n;
            }
            secondLast = n;
        }
        n = n->next;
    }

    if(firstLast) {
        firstLast->next = secondHead;
        head = firstHead;
    } else {
        head = secondHead;
    }

    if(secondLast) {
        secondLast->next = nullptr;
    }

    return head;
}

Node *constructList(const vector<int>& v)
{
    int sz = static_cast<int>(v.size());

    if(sz == 0)
        return nullptr;

    Node *head = new Node(v[0]);
    Node *prev = head;

    for(int i = 1; i < sz; ++i) {
        prev->next = new Node(v[i]);
        prev = prev->next;
    }

    return head;
}

bool compareList(Node* r1, Node* r2)
{
    Node *n1, *n2;

    n1 = r1;
    n2 = r2;
    while(n1 && n2) {
        if(n1->val != n2->val)
            return false;
        n1 = n1->next;
        n2 = n2->next;
    }

    return !n1 && !n2;
}

bool test(const vector<int>& v, const vector<int>& e, int x)
{
    Node *vp = constructList(v);
    Node *ep = constructList(e);
    vp = partitionList(vp, x);
    return compareList(vp, ep);
}

int main()
{
    vector<int> v1{8, 2, 3, 7, 9, 100, 4, 14, 15};
    vector<int> e1{2, 3, 4, 8, 7, 9, 100, 14, 15};
    assert(test(v1, e1, 7));
}
