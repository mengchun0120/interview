/*
Given a non-negative integer n, count all numbers with unique digits, x, where
0 <= x < 10^n.

Example: Input 2, Output 91

Explanation: The answer should be the total numbers in the range of 0 <= x <
100, excluding 11, 22, 33, 44, 55, 66, 77, 88, 99.
*/

#include <cassert>
#include <iostream>

using namespace std;

int countNumbers(int n)
{
    int sum = 10;
    int lastCount = 9;

    for(int i = 2; i <= n; ++i) {
        lastCount *= (10 - i + 1);
        sum += lastCount;
    }

    return sum;
}

int main()
{
    assert(countNumbers(2) == 10 + 9*9);
    assert(countNumbers(3) == 10 + 9*9 + 9*9*8);
    assert(countNumbers(4) == 10 + 9*9 + 9*9*8 + 9*9*8*7);
}

