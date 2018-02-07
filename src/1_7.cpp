#include <cassert>
#include <iostream>
#include <vector>
#include <unordered_map>

/*
Given an array a[] and an integer k, a[i] means flower at position a[i] will
blossom at day i. Find the first day that there are k slots between two
blooming flowers.
*/

using namespace std;

bool findFirstDay(unsigned int& first, unsigned int& second,
                   const vector<int>& a, unsigned int k)
{
    if(a.size() < 2) {
        return false;
    }

    unordered_map<int, unsigned int> map;
    unsigned int i;

    map.emplace(a[0], 0);
    for(i = 1; i < a.size(); ++i) {
        auto it = map.find(a[i]+k);
        if(it != map.end()) {
            first = it->second;
            second = i;
            return true;
        }

        it = map.find(a[i]-k);
        if(it != map.end()) {
            first = it->second;
            second = i;
            return true;
        }

        map.emplace(a[i], i);
    }

    return false;
}

void test(int testIndex, const vector<int>& a, unsigned int k,
          bool expected, unsigned int expectedSecond)
{
    unsigned int first, second;
    bool ret = findFirstDay(first, second, a, k);

    assert(ret == expected);
    if(expected) {
        assert(second == expectedSecond);
        assert(first >= 0 && first < second);
        assert((a[first]-a[second]) == static_cast<int>(k) ||
               (a[second]-a[first]) == static_cast<int>(k));
    }
    cout << "test" << testIndex << " successful" << endl;
}

int main(int argc, char* argv[])
{
    cout << "Testing 1_7 ..." << endl;

    vector<int> a1{};
    test(1, a1, 3, false, 0);

    vector<int> a2{3, 7, 5};
    test(2, a2, 2, true, 2);

    vector<int> a3{2, 6, 4, 3, 9};
    test(3, a3, 1, true, 3);

    vector<int> a4{4, 2, 1, 6, 5};
    test(4, a4, 9, false, 0);
}
