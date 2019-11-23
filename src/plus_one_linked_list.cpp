/*
Given a non-negative integer represented as non-empty a singly linked list of
digits, plus one to the integer. You may assume the integer don't contain any
leading zero, except the number 0 itself. The digits are stored such that the
most significant digit is at the head of the list.
*/

#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

struct Node {
    int digit;
    Node *next;

    Node(int d)
    : digit(d)
    , next(nullptr)
    {}
};

void printList(Node *head)
{
    Node *n = head;
    while(n) {
        cout << n->digit << ' ';
        n = n->next;
    }
    cout << endl;
}


Node *reverseList(Node *head)
{
    Node *prev = nullptr;
    Node *n = head;

    while(n->next) {
        Node *tmp = n->next;
        n->next = prev;
        prev = n;
        n = tmp;
    }

    n->next = prev;

    return n;
}

Node *plusOne(Node *head)
{
    if(!head)
        return nullptr;

    Node *n = reverseList(head);

    int carry = (n->digit + 1) / 10;
    n->digit = (n->digit + 1) % 10;

    if(carry > 0) {
        Node *m = n->next;
        while(m && m->digit == 9) {
            m->digit = 0;
            m = m->next;
        }

        if(m) {
            (m->digit)++;
        } else {
            head->next = new Node(1);
        }
    }

    Node *t = reverseList(n);

    return t;
}

Node *constructList(const vector<int> digits)
{
    int sz = static_cast<int>(digits.size());
    Node *head = new Node(digits[0]);
    Node *prev = head;
    for(int i = 1; i < sz; ++i) {
        Node *n = new Node(digits[i]);
        prev->next = n;
        prev = n;
    }
    return head;
}

int main()
{
    vector<int> v1{9, 9, 9};
    Node *h1 = constructList(v1);
    Node *r1 = plusOne(h1);
    printList(r1);

    vector<int> v2{2, 9, 9};
    Node *h2 = constructList(v2);
    Node *r2 = plusOne(h2);
    printList(r2);

    vector<int> v3{3, 0, 9};
    Node *h3 = constructList(v3);
    Node *r3 = plusOne(h3);
    printList(r3);
}
