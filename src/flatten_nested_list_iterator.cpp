/*
Given a nested ist of integers, implement an iterator to flatten it. Each
element is either an integer, or a list -- whose element may also be integers or
other lists.

Example 1: Input: [[1,1],2,[1,1]], Output: [1,1,2,1,1]
Explanation: By calling next repeatedly until hasNext returns false, the order
of elements returned next should be [1,1,2,1,1]

 Example 2: Input: [1,[4,[6]]], Output: [1,4,6]
*/

#include <cassert>
#include <vector>
#include <list>

using namespace std;

struct Elem {
    bool isList;
    union {
        int i;
        vector<Elem>* arr;
    } val;

    Elem(int k)
    : isList(false)
    {
        val.i = k;
    }

    Elem(vector<Elem>* l)
    : isList(true)
    {
        val.arr = l;
    }
};

struct StackItem {
    vector<Elem>* arr;
    unsigned int index;

    StackItem(vector<Elem>* a, unsigned int i)
    : arr(a)
    , index(i)
    {}
};

class NestedIterator {
    list<StackItem> stack;

public:
    NestedIterator(vector<Elem>* a);

    bool hasNext(int& i);

private:
    bool findNext();
};

NestedIterator::NestedIterator(vector<Elem>* a)
{
    stack.emplace_back(a, 0);
}

bool NestedIterator::hasNext(int& i)
{
    while(stack.size() > 0) {
        StackItem& t = stack.back();
        if(t.index >= t.arr->size()) {
            stack.pop_back();
            if(stack.size() > 0) {
                stack.back().index++;
            }
        } else {
            Elem& e = t.arr->at(t.index);
            if(!e.isList) {
                i = e.val.i;
                t.index++;
                return true;
            } else {
                stack.emplace_back(e.val.arr, 0);
            }
        }
    }

    return false;
}

void getList(vector<int>& r, vector<Elem>& a)
{
    NestedIterator it(&a);
    int i;
    while(it.hasNext(i)) {
        r.push_back(i);
    }
}

int main()
{
    vector<Elem> a{Elem(1), Elem(2)};
    vector<Elem> b{Elem(3), Elem(4)};
    vector<Elem> c{Elem(&a), Elem(1), Elem(&b)};
    vector<int> r1;
    vector<int> e1{1, 2, 1, 3, 4};
    getList(r1, c);
    assert(r1 == e1);

    vector<Elem> g;
    vector<Elem> f{Elem(&g)};
    vector<Elem> d{Elem(1), Elem(&a)};
    vector<Elem> e{Elem(4), Elem(&f), Elem(6), Elem(&d)};
    vector<int> r2;
    vector<int> e2{4, 6, 1, 1, 2};
    getList(r2, e);
    assert(r2 == e2);
}
