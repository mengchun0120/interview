#include <cassert>
#include <vector>
#include <iostream>
#include <utility>

using namespace std;

/*
Given an array of integers sorted in ascending order, find the starting and
ending position of a given target value. Your algorithm's runtime complexity
must in the order of O(logn). If the target is not found in the array, return
[-1,-1].
*/

pair<int,int> findRange(const vector<int>& arr, int val)
{
    int left = 0, right = arr.size() - 1;
    pair<int,int> result;

    result.first = -1;

    while(left <= right) {
        int mid = (left + right) >> 1;
        if(arr[mid] == val) {
            if(mid == 0 || arr[mid-1] < val) {
                result.first = mid;
                break;
            }

            right = mid - 1;
        } else if(arr[mid] < val) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    if(result.first == -1) {
        result.second = -1;
        return result;
    }

    left = result.first;
    right = arr.size() - 1;

    while(left <= right) {
        int mid = (left + right) >> 1;
        if(arr[mid] == val) {
            if(mid == (int)(arr.size()-1) || arr[mid+1] > val) {
                result.second = mid;
                break;
            }

            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return result;
}

int main()
{
    vector<int> a1{1,2,3,4,5,8,8,8,8,8,9,10};
    pair<int,int> e1(5,9);
    pair<int,int> r1 = findRange(a1,8);

    assert(e1 == r1);

    pair<int,int> e2(0,0);
    pair<int,int> r2 = findRange(a1,1);

    assert(e2 == r2);

    pair<int,int> e3(11,11);
    pair<int,int> r3 = findRange(a1,10);

    assert(e3 == r3);

    pair<int,int> e4(-1,-1);
    pair<int,int> r4 = findRange(a1, 11);

    assert(e4 == r4);
}
