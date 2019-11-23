/*
Given a positive number, return its corresponding column title as appear in an
Excel sheet. For example: 1->A, 2->B, 3->C ... 26->Z, 27->AA
*/

#include <cassert>
#include <string>
#include <list>
#include <iostream>

using namespace std;

string getExcelTitle(int n)
{
    list<char> r;
    while(n > 0) {
        int k = (n - 1) % 26;
        r.push_front('A' + k);
        n = (n - 1) / 26;
    }

    string s(r.begin(), r.end());
    return s;
}

int main()
{
    string r1 = getExcelTitle(1);
    assert(r1 == "A");
    string r2 = getExcelTitle(26);
    assert(r2 == "Z");
    string r3 = getExcelTitle(28);
    assert(r3 == "AB");
    string r4 = getExcelTitle(701);
    assert(r4 == "ZY");
}
