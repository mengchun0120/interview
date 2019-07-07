#include <cassert>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

/*
Implement next permutation, which rearranges numbers into the lexicographically
next greater permutation of numbers. If such arrangement is not possible, it
must rearrange it as the lowest possible order (i.e., sored in ascending order)
The replacement must be in-place, do not allocate extra memory.
*/

void nextPermutation(vector<int>& a)
{
    int i = a.size() - 1;
    for(; i >= 1; --i) {
        if(a[i-1] < a[i]) {
            break;
        }
    }

    if(i >= 1) {
        int j = a.size() - 1;
        for(; j >= i; --j) {
            if(a[j] > a[i-1]) {
                break;
            }
        }

        swap(a[j], a[i-1]);
    }

    int l = i, r = a.size() - 1;
    while(l < r) {
        swap(a[l], a[r]);
        ++l;
        --r;
    }
}

bool operator==(const vector<int>& a1, const vector<int>& a2)
{
    if(a1.size() != a2.size()) {
        return false;
    }

    for(size_t i = 0; i < a1.size(); ++i) {
        if(a1[i] != a2[i]) {
            return false;
        }
    }

    return true;
}

namespace std {

template <typename T>
ostream& operator<<(ostream& os, const vector<T>& l)
{
    os << '[';
    if(l.size() > 0) {
        auto it = l.begin();
        os << *it;
        for(++it; it != l.end(); ++it) {
            os << ',' << *it;
        }
    }
    os << ']';
    return os;
}

}

int main()
{
    vector<int> a1{0, 1, 2, 3};
    vector<int> r1{0, 1, 3, 2};

    nextPermutation(a1);
    assert(a1 == r1);

    vector<int> a2{2, 3, 1, 0};
    vector<int> r2{3, 0, 1, 2};

    nextPermutation(a2);
    assert(a2 == r2);

    vector<int> a3{3, 2, 1, 0};
    vector<int> r3{0, 1, 2, 3};

    nextPermutation(a3);
    assert(a3 == r3);
}
