/*
Given an array of n integers and an integer target, find three integers in the
array such that the sum is closest to target. Return the sum of the three
integers. You may assume that each input would have exactly one solution.

Example:
Input: [-1, 2, 1, -4], and target=1
The sum that is closest to the target is 2=-1+1+2
*/

#include <cassert>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int abs(int a, int b)
{
    if(a >= b) {
        return a - b;
    }
    return b - a;
}

void printArr(const vector<int>& a)
{
    for(auto it = a.begin(); it != a.end(); ++it) {
        cout << *it << ' ';
    }
    cout << endl;
}

int getClosest3Sum(vector<int>& result, const vector<int>& arr, int target)
{
    vector<int> a(arr);
    int sz = a.size();

    sort(a.begin(), a.end());

    result.resize(3);
    result[0] = a[0];
    result[1] = a[1];
    result[2] = a[2];

    int closest = a[0] + a[1] + a[2];
    for(int i = 0; i < sz - 2; ++i) {
        int low = i + 1;
        int high = sz - 1;

        while(low < high) {
            int sum = a[i] + a[low] + a[high];

            if(sum == target) {
                result[0] = a[i];
                result[1] = a[low];
                result[2] = a[high];
                return sum;
            }

            if(abs(sum, target) < abs(closest, target)) {
                closest = sum;
                result[0] = a[i];
                result[1] = a[low];
                result[2] = a[high];
            }

            if(target < sum) {
                high--;
            } else {
                low++;
            }
        }
    }

    return closest;
}

int main()
{
    vector<int> a1{-1, 2, 1, 4};
    vector<int> r1;
    int c1 = getClosest3Sum(r1, a1, 2);
    cout << c1 << endl;
    printArr(r1);

    c1 = getClosest3Sum(r1, a1, 4);
    cout << c1 << endl;
    printArr(r1);
}
