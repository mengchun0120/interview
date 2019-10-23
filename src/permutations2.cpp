/*
Given a collection of numbers that might contain duplicates, return all possible
unique permutations.

Example:
Input: [1,1,2]
Output:
[
    [1,1,2]
    [1,2,1]
    [2,1,1]
]
*/

#include <cassert>
#include <vector>
#include <list>
#include <iostream>

using namespace std;

void print(const vector<int>& r)
{
    for(auto it = r.begin(); it != r.end(); ++it) {
        cout << *it << ' ';
    }
    cout << endl;
}

void print(const list<vector<int>>& r)
{
    for(auto it = r.begin(); it != r.end(); ++it) {
        print(*it);
    }
}

void addPermutations(list<vector<int>>& r, const vector<int>& p,
                    int num, int pos)
{
    int count = static_cast<int>(p.size());
    vector<int> t(count+1);

    int i, j;

    for(i = 0, j = 0; i < pos; ++i, ++j) {
        t[j] = p[i];
    }

    t[j++] = num;

    for(; i < count; ++i, ++j) {
        t[j] = p[i];
    }

    r.push_back(move(t));
}

void genPermutations(list<vector<int>>& r, const vector<int>& p, int num)
{
    int count = static_cast<int>(p.size());
    if(count == 0) {
        return;
    }

    int i;

    addPermutations(r, p, num, 0);

    i = 0;
    while(i < count) {
        if(p[i] == num) {
            for(++i; i < count; ++i) {
                if(p[i] != num) {
                    break;
                }
            }
        }

        if(i == count) {
            break;
        }

        addPermutations(r, p, num, i+1);
        ++i;
    }
}

void getPermutations(list<vector<int>>& results, const vector<int>& numbers)
{
    int count = static_cast<int>(numbers.size());
    vector<list<vector<int>>> records(count);

    records[0].push_back(vector<int>{numbers[0]});
    for(int i = 1; i < count; ++i) {
        list<vector<int>>& prev = records[i-1];
        list<vector<int>>& cur = records[i];

        for(auto it = prev.begin(); it != prev.end(); ++it) {
            genPermutations(cur, *it, numbers[i]);
        }
    }

    results = move(records[count-1]);
}

int main()
{
    vector<int> numbers1{1, 1, 2};
    list<vector<int>> results1;
    getPermutations(results1, numbers1);
    print(results1);

    cout << endl;

    vector<int> numbers2{2, 2, 1, 3};
    list<vector<int>> results2;
    getPermutations(results2, numbers2);
    print(results2);
}
