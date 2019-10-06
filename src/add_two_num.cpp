#include <cassert>
#include <vector>
#include <iostream>

/*
You are given two non-empty list of linked
lists representing non-negative integers.
The digits are stored in reverse order and
each of their nodes contains a single
digit. Add the two numbers and return it
as a linked list.

You may assume the two numbers don't
contain any leading zero, except the number
zero itself.
 */

using namespace std;

struct node {
    int digit;
    node *next;

    node(int d)
    : digit(d)
    , next(nullptr)
    {}
};

node *addDigit(int d1, int d2, int& c)
{
    int s =  d1 + d2 + c;
    c = s / 10;
    s %= 10;
    node *t = new node(s);
    return t;
}

node *add(node *n1, node *n2)
{
    node *r, *p1, *p2, *p;
    int carry = 0;

    r = addDigit(n1->digit,
                 n2->digit,
                 carry);
    p = r;
    p1 = n1->next;
    p2 = n2->next;
    while(p1 && p2) {
        p->next = addDigit(p1->digit,
                           p2->digit,
                           carry);
        p = p->next;

        p1 = p1->next;
        p2 = p2->next;
    }

    if(p1 || p2) {
        node *t = p1 ? p1 : p2;
        while(t) {
            p->next = addDigit(t->digit,
                               0,
                               carry);
            p = p->next;

            t = t->next;
        }
    }

    if(carry > 0) {
        p->next = new node(carry);
    }

    return r;
}

node *createNum(const vector<int>& a)
{
    node *r, *p;
    unsigned int i;

    r = new node(a[0]);
    p = r;
    for(i = 1; i < a.size(); ++i) {
        p->next = new node(a[i]);
        p = p->next;
    }

    return r;
}

bool equal(node *n1, node *n2)
{
    node *p1, *p2;

    p1 = n1;
    p2 = n2;
    while(p1 && p2) {
        if(p1->digit != p2->digit) {
            return false;
        }

        p1 = p1->next;
        p2 = p2->next;
    }

    return p1 == nullptr && p2 == nullptr;
}

void freeList(node *n)
{
    node *p, *q;

    for(p = n; p; p = q) {
        q = p->next;
        delete p;
    }
}

void print(const node *n)
{
    while(n) {
        cout << n->digit << ' ';
        n = n->next;
    }
    cout << endl;
}

bool test(const vector<int>& n1,
          const vector<int>& n2,
          const vector<int>& e)
{
    node *p1 = createNum(n1);
    node *p2 = createNum(n2);
    node *f = createNum(e);
    node *r = add(p1, p2);
    bool b = equal(f, r);
    freeList(p1);
    freeList(p2);
    freeList(f);
    freeList(r);
    return b;
}

int main()
{
    vector<int> n11{0, 8, 7};
    vector<int> n12{1, 3, 9};
    vector<int> r1{1, 1, 7, 1};
    assert(test(n11, n12, r1));

    vector<int> n21{9};
    vector<int> n22{9, 9, 9};
    vector<int> r2{8, 0, 0, 1};
    assert(test(n21, n22, r2));
}
