#include <cassert>
#include <iostream>
#include <vector>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <sstream>
#include <functional>
#include <string>
#include <utility>

using namespace std;

/*
Given an array S of n integers, are there elements a, b, c in S such that
a+b+c = 0? Find all unique triplets in the array which gives the sum of zero.
Note: The solution must not contain duplicate triplets.
*/

struct VectorHash {
    size_t operator()(const vector<int>& arr) const
    {
        ostringstream oss;
        for(auto it = arr.begin(); it != arr.end(); ++it) {
            oss << *it << ',';
        }
        return hash<string>{}(oss.str());
    }
};

struct VectorEqual {
    bool operator()(const vector<int>& a1, const vector<int>& a2) const
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
};

typedef unordered_set<vector<int>, VectorHash, VectorEqual> VectorSet;
typedef unordered_map<int, VectorSet> SumVectorSetMap;

void constructPair(vector<int>& v, int i1, int i2)
{
    if(i1 <= i2) {
        v[0] = i1;
        v[1] = i2;
    } else {
        v[0] = i2;
        v[1] = i1;
    }
}

void constructTriplet(vector<int>& v, const vector<int>& pair, int i)
{
    if(i <= pair[0]) {
        v[0] = i;
        v[1] = pair[0];
        v[2] = pair[1];
    } else if(pair[1] <= i) {
        v[0] = pair[0];
        v[1] = pair[1];
        v[2] = i;
    } else {
        v[0] = pair[0];
        v[1] = i;
        v[2] = pair[1];
    }
}

void find3Sum(vector<vector<int>>& results, const vector<int>& arr)
{
    results.clear();

    if(arr.size() < 3) {
        return;
    }

    SumVectorSetMap sumVecSetMap;
    VectorSet resultSet;
    vector<int> pair(2);
    vector<int> triplet(3);

    constructPair(pair, arr[0], arr[1]);
    sumVecSetMap[arr[0]+arr[1]].insert(pair);

    for(size_t i = 2; i < arr.size(); ++i) {
        auto it = sumVecSetMap.find(-arr[i]);
        if(it != sumVecSetMap.end()) {
            for(auto it1 = it->second.begin(); it1 != it->second.end(); ++it1) {
                constructTriplet(triplet, *it1, arr[i]);
                resultSet.insert(triplet);
            }
        }

        for(size_t j = 0; j < i; ++j) {
            constructPair(pair, arr[j], arr[i]);
            sumVecSetMap[arr[j]+arr[i]].insert(pair);
        }
    }

    if(resultSet.size() > 0) {
        size_t k = 0;
        results.resize(resultSet.size());
        for(auto it = resultSet.begin(); it != resultSet.end(); ++it, ++k) {
            results[k] = move(*it);
        }
    }
}

bool compareResults(const vector<vector<int>>& r, const vector<vector<int>>& e)
{
    if(r.size() != e.size()) {
        return false;
    }

    VectorEqual equal;

    for(size_t i = 0; i < e.size(); ++i) {
        size_t j;
        for(j = 0; j < r.size(); ++j) {
            if(equal(e[i],r[j])) {
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
    vector<int> a1{1, 2, -3};
    vector<vector<int>> e1{{-3,1,2}};
    vector<vector<int>> r1;

    find3Sum(r1, a1);
    assert(compareResults(r1, e1));

    vector<int> a2{5, 3, -7, 2, -5, 0, 3, -6};
    vector<vector<int>> e2{
        {-7, 2, 5},
        {-5, 0, 5},
        {-5, 2, 3},
        {-6, 3, 3}
    };
    vector<vector<int>> r2;

    find3Sum(r2, a2);
    assert(compareResults(r2, e2));
}

