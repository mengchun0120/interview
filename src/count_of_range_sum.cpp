/*
Given an integer array, return the number of range sums that live in
[lower, upper] inclusive. Range sum S(i,j) is defined as the sum of
the elements in the array between indices i and j (i<=j) inclusive.

Note: A naive algorithm of O(n^2) is trivial. You MUST do better than
that.
*/

#include <cassert>
#include <iostream>
#include <vector>
#include <utility>
#include <list>
#include <algorithm>

using namespace std;

struct Elem {
    int sum;
    unsigned int start;
};

bool compare(const Elem& e1, const Elem& e2)
{
    return e1.sum < e2.sum;
}

int findStartIdx(const vector<Elem>& v, int lower)
{
    if(v[0].sum >= lower)
        return 0;

    int left = 0;
    int right = v.size() - 1;

    while(left < right) {
        int mid = (left + right) / 2;
        if(v[mid].sum >= lower) {
            if(v[mid-1].sum < lower) {
                return mid;
            }

            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    return left;
}

int findEndIdx(const vector<Elem>& v, int upper)
{
    if(v.back().sum <= upper)
        return v.size() - 1;

    int left = 0;
    int right = v.size() - 1;

    while(left < right) {
        int mid = (left + right) / 2;
        if(v[mid].sum <= upper) {
            if(v[mid+1].sum > upper) {
                return mid;
            }

            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return left;
}

void getMergeSum(list<pair<int,int>>& result, const vector<int>& arr,
                 int start1,  int end1, int start2,  int end2,
                 int lower, int upper)
{
    int sum, i;
    vector<Elem> v(end1 - start1 + 1);

    sum = 0;
    i = 0;
    for(int s = end1; s >= start1; --s, ++i) {
        sum += arr[s];
        v[i].sum = sum;
        v[i].start = s;
    }

    sort(v.begin(), v.end(), compare);

    sum = 0;
    for(int e = start2; e <= end2; ++e) {
        sum += arr[e];

        if(sum + v[0].sum > upper || sum + v.back().sum < lower)
            continue;

        int startIdx = findStartIdx(v, lower - sum);
        int endIdx = findEndIdx(v, upper - sum);

        for(int i = startIdx; i <= endIdx; ++i) {
            result.emplace_back(v[i].start, e);
        }
    }
}

void countRangeSum(list<pair<int,int>>& result, const vector<int>& arr,
                   int lower, int upper)
{
    int sz = arr.size();
    for(int i = 0; i < sz; ++i) {
        if(arr[i] >= lower && arr[i] <= upper)
            result.emplace_back(i, i);
    }

    int step = 1;
    while(step < sz) {
        int start1, end1, start2, end2;

        start1 = 0;
        end1 = step - 1;
        start2 = end1 + 1;
        while(start2 < sz) {
            end2 = end1 + step;
            if(end2 >= sz) {
                end2 = arr.size() - 1;
            }

            getMergeSum(result, arr, start1, end1, start2, end2, lower, upper);

            start1 = end2 + 1;
            end1 = start1 + step - 1;
            start2 = end1 + 1;
        }

        step *= 2;
    }
}

void countRangeSum2(list<pair<int,int>>& result, const vector<int>& arr,
                    int lower, int upper)
{
    for(int i = 0; i < static_cast<int>(arr.size()); ++i) {
        int sum = 0;
        for(int j = i; j >= 0; --j) {
            sum += arr[j];
            if(sum >= lower && sum <= upper) {
                result.emplace_back(j, i);
            }
        }
    }
}

ostream& operator<<(ostream& os, const list<pair<int,int>>& r)
{
    os << '[';
    if(r.size() > 0) {
        auto it = r.begin();
        os << '(' << it->first << ',' << it->second << ')';
        for(++it; it != r.end(); ++it) {
            os << ", (" << it->first << ',' << it->second << ')';
        }
    }
    os << ']';
    return os;
}

bool test(const vector<int>& arr, int lower, int upper)
{
    list<pair<int,int>> r1, r2;

    countRangeSum(r1, arr, lower, upper);
    countRangeSum2(r2, arr, lower, upper);

    if(r1.size() != r2.size())
        return false;

    for(auto it2 = r2.begin(); it2 != r2.end(); ++it2) {
        auto it1 = r1.begin();
        for(; it1 != r1.end(); ++it1) {
            if(*it1 == *it2)
                break;
        }
        if(it1 == r1.end())
            return false;
    }

    return true;
}

int main()
{
    vector<int> a1{1, 2, 3, 7, 9};
    assert(test(a1, 5, 10));

    vector<int> a2{3, 2, -1, 3, 4, 7, 8, 12, 1, 0};
    assert(test(a2, 15, 30));
}
