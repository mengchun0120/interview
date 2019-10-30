/*
Write a program to find the nth super ugly number. Super ugly numbers are
positive numbers whose all prime factors are in the given list of primes of
size k.

Example:
Input: n=12, primes=[2,7,13,19], output: 32

1 2 2*2 7 2*2*2 13 2*7 2*2*2*2 19 2*13 2*2*7 2*2*2*2*2 2*19 2*2*13 2*2*2*7

Note:
1 is a super ugly number for any given primes. The given numbers in primes
are in ascending order. 0 < k <= 100, 0 < n <= 106, 0 < primes[i] < 1000.
The nth super ugly number is guaranteed to fit in a 32-bit signed integer.
*/

#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

int findLowestUpperBound(const vector<int>& a, int sz, int factor)
{
    double target = (double)a[sz-1] / (double)factor;

    if(target < a[0]) {
        return a[0] * factor;
    }

    int low = 0;
    int high = sz - 1;

    while(low + 1 < high) {
        int mid = (low + high) / 2;
        if((double)a[mid] <= (double)target) {
            low = mid;
        } else {
            high = mid;
        }
    }

    return a[high] * factor;
}

void f()
{
}

int findUglyNumber(int n, const vector<int>& primes)
{
    int np = primes.size();
    vector<int> a(n);
    a[0] = 1;
    for(int i = 1; i < n; ++i) {
        int lowest = findLowestUpperBound(a, i, primes[0]);
        for(int j = 1; j < np; ++j) {
            int l = findLowestUpperBound(a, i, primes[j]);
            if(l < lowest) {
                lowest = l;
            }
        }
        cout << (i+1) << ':' << lowest << ' ';
        a[i] = lowest;
    }
    cout << endl;
    return a[n-1];
}

int main()
{
    vector<int> p1{2, 7, 13, 19};
    int r1 = findUglyNumber(12, p1);
    cout << r1 << endl;
}
