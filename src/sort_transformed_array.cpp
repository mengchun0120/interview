/*
Given a sorted array of integers nums and integer values a, b, and c. Apply
a quadratic function of the form f(x) = ax^2 + bx + c to each element x in the
array. The returned array must be in sorted order. Expected time complexity:
O(n)
*/

#include <cassert>
#include <iostream>
#include <vector>
#include <list>

using namespace std;

void sortTransformed(vector<int>& result, const vector<int>& nums,
                     int a, int b, int c)
{
    int sz = static_cast<int>(nums.size());
    if(sz == 0)
        return;

    double turningPoint = -(double)b / (2.0 * (double)a);
    list<int> first, second;
    int i;

    for(int i = 0; i < sz; ++i) {
        int t = nums[i];
        int r = a*t*t + b*t + c;
        if((double)t <= turningPoint) {
            first.push_front(r);
        } else {
            second.push_back(r);
        }
    }

    result.resize(sz);

    i = 0;
    auto it1 = first.begin();
    auto it2 = second.begin();
    while(it1 != first.end() && it2 != second.end()) {
        if(*it1 < *it2) {
            result[i] = *it1;
            ++it1;
        } else {
            result[i] = *it2;
            ++it2;
        }
        ++i;
    }

    if(it1 != first.end()) {
        for(; it1 != first.end(); ++it1, ++i) {
            result[i] = *it1;
        }
    } else if(it2 != second.end()) {
        for(; it2 != second.end(); ++it2, ++i) {
            result[i] = *it2;
        }
    }
}

ostream& operator<<(ostream& os, const vector<int>& a)
{
    os << '[';
    if(a.size() > 0) {
        os << a[0];
        for(int i = 1; i < static_cast<int>(a.size()); ++i) {
            os << ", " << a[i];
        }
    }
    os << ']';
    return os;
}

int main()
{
    vector<int> a1{-3, -2, -1, 0, 4, 5, 7};
    vector<int> r1;
    sortTransformed(r1, a1, 1, 2, 1);
    cout << r1 << endl;
}
