/*
Implement the following operations of a stack using queues.
push(x) -- push element x onto stack.
pop() -- removes the element on top of the stack.
top() -- get the top element.
empty() -- return wheter the stack is empty.
You must use only standard operations of a queue -- which means only push to
back, peek/pop form front, size, and is empty operations ar evalid.
*/

#include <cassert>
#include <list>
#include <iostream>
#include <stdexcept>

using namespace std;

class Stack {
public:
    Stack();

    ~Stack();

    void push(int x);

    bool pop();

    bool top(int& k);

    bool empty();

private:
    list<int> q1, q2;
    list<int>* q;
};

Stack::Stack()
{
    q = &q1;
}

Stack::~Stack()
{
}

void Stack::push(int x)
{
    list<int>* other = q == &q1 ? &q2 : &q1;
    other->push_back(x);
    while(q->size() > 0) {
        other->push_back(q->front());
        q->pop_front();
    }
    q = other;
}

bool Stack::pop()
{
    if(empty()) {
        return false;
    }
    q->pop_front();
    return true;
}

bool Stack::top(int& k)
{
    if(empty()) {
        return false;
    }
    k = q->front();
    return true;
}

bool Stack::empty()
{
    return q->size() == 0;
}

int main()
{
    Stack stack;
    stack.push(1);
    stack.push(2);
    int k;
    assert(stack.top(k) && k == 2);
    stack.pop();
    stack.push(3);
    assert(stack.top(k) && k == 3);
    stack.pop();
    assert(stack.top(k) && k == 1);
    stack.pop();
    assert(stack.empty());
}
