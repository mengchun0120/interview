#include <cassert>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <utility>

/*
Find the Kth most Frequent Number in an Array. Example: arr[] = {1, 2, 3, 2, 1,
2, 2, 2, 3}, k = 2, Result: 3. Because '3' is the second most occurring
element. Follow up: What if the array is extremely lairge?
*/

using namespace std;

bool compare(const pair<int,int>& p1, const pair<int,int>& p2)
{
    return p1.second > p2.second;
}

bool findKthMostFrequent(int& answer, const vector<int>& arr, unsigned int k)
{
    unordered_map<int,int> records;
    unsigned int i;

    for(i=0; i < arr.size(); ++i) {
        auto it = records.find(arr[i]);
        if(it == records.end()) {
            records[arr[i]] = 1;
        } else {
            (it->second)++;
        }
    }

    if(records.size() < k) {
        return false;
    }

    vector<pair<int,int>> sorted(records.size());

    i = 0;
    for(auto it=records.begin(); it != records.end(); ++it, ++i) {
        sorted[i] = *it;
    }

    sort(sorted.begin(), sorted.end(), compare);

    answer = sorted[k-1].first;

    return true;
}

void test(int testIndex, const vector<int>& arr, unsigned int k,
          bool found, int expectedAnswer)
{
    int answer;
    bool ret = findKthMostFrequent(answer, arr, k);

    assert(ret == found);
    if(found) {
        assert(answer == expectedAnswer);
    }

    cout << "test" << testIndex << " successful" << endl;
}

int main(int argc, char* argv[])
{
    cout << "Running 1_9 ..." << endl;

    vector<int> a1{1, 2, 3, 2, 3, 3};
    int testIndex=1;
    test(testIndex++, a1, 100, false, 0);
    test(testIndex++, a1, 3, true, 1);
    test(testIndex++, a1, 1, true, 3);

    vector<int> a2;
    test(testIndex++, a2, 1, false, 0);

    vector<int> a3{2, 2, 3, 3, 3, 3, 4, 4, 4};
    test(testIndex++, a3, 1, true, 3);
    test(testIndex++, a3, 2, true, 4);
}

