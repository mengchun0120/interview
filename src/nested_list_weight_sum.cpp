/*
Given a nested list of integers, return the sum of all integers in the list
weighted by their depth. Each element is either an integer, or a list -- whose
elements may also be integers or other lists.

Example 1: Input: [[1,1],2,[1,1]]
Output: 10
Explanation: Four 1's at depth 2, one 2 at depth 1.

Example 2: Input [1, [4, [6]]]
Output: 27
Explanation: One 1 at depth 1, one 4 at depth 2, one 6 at depth 3; 1 + 4*2 +
6*3 = 27
*/

#include <cassert>
#include <vector>
#include <list>

using namespace std;

struct Elem {
    bool isList;
    union {
        int i;
        vector<Elem>* list;
    } val;

    Elem(int k)
    : isList(false)
    {
        val.i = k;
    }

    Elem(vector<Elem>* l)
    : isList(true)
    {
        val.list = l;
    }
};

struct StackItem {
    vector<Elem>* list;
    unsigned int depth;
    unsigned int index;

    StackItem(vector<Elem>* l, unsigned int d, unsigned int i)
    : list(l)
    , depth(d)
    , index(i)
    {}
};

int getSum(vector<Elem>& l)
{
    if(l.size() == 0) {
        return 0;
    }

    list<StackItem> stack;
    int sum = 0;

    stack.emplace_back(&l, 1, 0);
    while(stack.size() > 0) {
        StackItem& item = stack.back();
        if(item.index >= item.list->size()) {
            stack.pop_back();
        } else {
            Elem& elem = (*(item.list))[item.index];
            if(elem.isList) {
                stack.emplace_back(elem.val.list, item.depth+1, 0);
            } else {
                sum += elem.val.i * item.depth;
            }
            item.index++;
        }
    }

    return sum;
}

int main()
{
    vector<Elem> a{Elem(1), Elem(2)};
    vector<Elem> b{Elem(3), Elem(4)};
    vector<Elem> c{Elem(&a), Elem(1), Elem(&b)};
    assert(21 == getSum(c));

    vector<Elem> d{Elem(1), Elem(&a)};
    vector<Elem> e{Elem(4), Elem(6), Elem(&d)};
    assert(21 == getSum(e));
}

