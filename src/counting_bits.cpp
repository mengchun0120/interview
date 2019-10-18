/*
Given a non negative integer num. For every numbers i in the range 0 <= i <= 
num, calculate the number of 1's in their binary representation and return them
as an array.

Example 1: Input 2, Output [0, 1, 1]
Example 2: Input 5, Output [0, 1, 1, 2, 1, 2]

Follow up: It is very easy to come up with a solution with run time
O(n*sizeof(integer)). But can you do it in linear time O(n), possibly in a
single pass? Space complexiy should be O(n).
*/

#include <cassert>
#include <vector>
#include <list>

using namespace std;

struct Scope {
    unsigned start;
    unsigned end;

    Scope(unsigned s, unsigned e)
    : start(s)
    , end(e)
    {}
};

void countBits(vector<int>& c, unsigned int n)
{
    c.push_back(0);

    if(n < 1) {
        return;
    }

    list<Scope> scopes;
    int newCount;

    scopes.emplace_front(0,0);
    c.push_back(1);

    for(unsigned int i = 2; i <=n; ++i) {
        auto it = scopes.begin();

        if(it->start == 0) {
            newCount = c[i-1] - it->end + it->start;

            unsigned int newEnd = it->end + 1;

            auto it2 = it;
            ++it;

            if(it == scopes.end() || it->start > newEnd + 1) {
                it2->start = newEnd;
                it2->end = newEnd;
            } else {
                scopes.pop_front();
                it->start = newEnd;
            }

        } else {
            newCount = c[i-1] + 1;

            if(it->start == 1) {
                it->start = 0;
            } else {
                scopes.emplace_front(0,0);
            }
        }

        c.push_back(newCount);
    }
}

int main()
{
    vector<int> r1;
    vector<int> e1{0};
    countBits(r1, 0);
    assert(r1 == e1);

    vector<int> r2;
    vector<int> e2{0,1};
    countBits(r2, 1);
    assert(r2 == e2);

    vector<int> r3;
    vector<int> e3{0,1,1,2,1};
    countBits(r3, 4);
    assert(r3 == e3);

    vector<int> r4;
    vector<int> e4{0,
                   1,1,2,1,2,2,3,1,2,2,
                   3,2,3,3,4,1,2,2,3,2,
                   3,3,4,2,3,3,4,3,4,4};
    countBits(r4, 30);
    assert(r4 == e4);
}
