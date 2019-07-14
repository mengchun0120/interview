#include <cassert>
#include <iostream>
#include <vector>
#include <utility>

using namespace std;

/*
Given a set of candidate numbers (C) (without duplicates) and a target number
T, find all unique combinations in C where the candidate numbers sum to T. The
same repeated number may be chosen from C unlimited number of times. 

Note:
- All numbers (including target) will be positive integers.
- The solution set must not contain duplicate combintations.
*/

vector<vector<int>> findCombinationSums(const vector<int>& arr, size_t findSize,
                                        int target)
{
    vector<vector<int>> result;
    size_t count;

    if(findSize == 1) {
        if((target % arr[0]) == 0) {
            vector<int> r;

            count = target / arr[0];
            r.resize(count);
            for(size_t i = 0; i < count; ++i) {
                r[i] = arr[0];
            }

            result.push_back(move(r));
        }
    } else {
        result = move(findCombinationSums(arr, findSize-1, target));

        int elem = arr[findSize-1];
        int reminder = target - elem;

        for(count = 1; reminder >= 0; ++count, reminder-=elem) {
            if(reminder > 0) {
                vector<vector<int>> tmp =
                        move(findCombinationSums(arr, findSize-1, reminder));
                for(size_t i = 0; i < tmp.size(); ++i) {
                    vector<int> r = move(tmp[i]);

                    for(size_t j = 0; j < count; ++j) {
                        r.push_back(elem);
                    }

                    result.push_back(move(r));
                }
            } else {
                vector<int> r(count);
                for(size_t i = 0; i < count; ++i) {
                    r[i] = elem;
                }

                result.push_back(move(r));
            }
        }
    }

    return result;
}

vector<vector<int>> findCombinationSums(const vector<int>& arr, int target)
{
    return findCombinationSums(arr, arr.size(), target);
}

bool containSame(const vector<int>& r, const vector<int>& e)
{
    if(r.size() != e.size()) {
        return false;
    }

    for(size_t i = 0; i < e.size(); ++i) {
        size_t j;
        for(j = 0; j < r.size(); ++j) {
            if(r[j] == e[i]) {
                break;
            }
        }

        if(j == r.size()) {
            return false;
        }
    }

    return true;
}

bool compareResults(const vector<vector<int>>& r, const vector<vector<int>>& e)
{
    if(r.size() != e.size()) {
        return false;
    }

    for(size_t i = 0; i < e.size(); ++i) {
        size_t j;
        for(j = 0; j < r.size(); ++j) {
            if(containSame(e[i],r[j])) {
                break;
            }
        }

        if(j == r.size()) {
            return false;
        }
    }

    return true;
}

namespace std {

ostream& operator<<(ostream& os, const vector<vector<int>>& a)
{
    os << '[' << endl;
    for(size_t i = 0; i < a.size(); ++i) {
        const vector<int>& b = a[i];
        os << '[';
        for(size_t j = 0; j < b.size(); ++j) {
            os << b[j] << ',';
        }
        os << ']' << endl;
    }
    os << ']';
    return os;
}

}

int main()
{
    vector<int> a1{2, 3, 4, 5};
    int t1 = 7;
    vector<vector<int>> e1{
        {2,5},
        {3,4},
        {2,2,3}
    };

    vector<vector<int>> r1 = move(findCombinationSums(a1, t1));
    assert(compareResults(r1, e1));

    vector<int> a2{3, 4, 5, 6, 7};
    int t2 = 11;
    vector<vector<int>> e2{
        {3,3,5},
        {4,7},
        {5,6},
        {3,4,4}
    };

    vector<vector<int>> r2 = move(findCombinationSums(a2, t2));
    assert(compareResults(r2, e2));
}
