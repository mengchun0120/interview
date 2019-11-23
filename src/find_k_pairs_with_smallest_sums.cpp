/*
You are given two integer arrays sorted in ascending order. Define a pair (u,v)
consists of one element from the first array and another from the second array.
Find the k pairs with the smallest sums.
*/

#include <cassert>
#include <iostream>
#include <vector>
#include <utility>
#include <list>

using namespace std;

void addPair1(list<pair<int,int>>& pairs, int i, int j)
{
    pairs.emplace_back(i,j);
}

void addPair2(list<pair<int,int>>& pairs, int i, int j)
{
    pairs.emplace_back(j,i);
}

typedef void (*AddFunc)(list<pair<int,int>>&, int, int);

struct HeapNode {
    int idx1, idx2;
    int sum;
};

void heapifyDown(vector<HeapNode>& heap, int heapSize)
{
    int i, leftChild, rightChild;
    HeapNode tmp = heap[0];

    i = 0;
    leftChild = 1;
    while(leftChild < heapSize) {
        int minIdx = i;

        if(heap[leftChild].sum < heap[minIdx].sum) {
            minIdx = leftChild;
        }

        rightChild = leftChild + 1;
        if(rightChild < heapSize && heap[rightChild].sum < heap[minIdx].sum) {
            minIdx = rightChild;
        }

        if(minIdx == i)
            break;

        heap[i] = heap[minIdx];
        i = minIdx;
        leftChild = 2 * i + 1;
    }

    heap[i] = tmp;
}

void findSmallestPairs(list<pair<int,int>>& pairs,
                       const vector<int>& a1,
                       const vector<int>& a2,
                       int k)
{
    if(k == 0 || a1.size() == 0 || a2.size() == 0)
        return;

    const vector<int> *p1, *p2;
    AddFunc addFunc;
    int heapSize;

    if(a1.size() <= a2.size()) {
        p1 = &a1;
        p2 = &a2;
        addFunc = addPair1;
        heapSize = static_cast<int>(a1.size());
    } else {
        p1 = &a2;
        p2 = &a1;
        addFunc = addPair2;
        heapSize = static_cast<int>(a2.size());
    }

    vector<HeapNode> heap(heapSize);
    for(int i = 0; i < heapSize; ++i) {
        heap[i].idx1 = i;
        heap[i].idx2 = 0;
        heap[i].sum = (*p1)[i] + (*p2)[0];
    }

    for(int i = 0; i < k; ++i) {
        HeapNode& h = heap[0];
        addFunc(pairs, h.idx1, h.idx2);
        (h.idx2)++;
        if(h.idx2 < static_cast<int>(p2->size())) {
            h.sum = (*p1)[h.idx1] + (*p2)[h.idx2];
            heapifyDown(heap, heapSize);
        } else if(heapSize > 1) {
            heap[0] = heap[heapSize-1];
            --heapSize;
            heapifyDown(heap, heapSize);
        } else {
            break;
        }
    }
}

ostream& operator<<(ostream& os, const list<pair<int,int>>& pairs)
{
    os << '[';
    if(pairs.size() > 0) {
        auto it = pairs.begin();
        os << '(' << it->first << ',' << it->second << ')';
        for(++it; it != pairs.end(); ++it) {
            os << ", " << '(' << it->first << ',' << it->second << ')';
        }
    }
    os << ']';
    return os;
}

int main()
{
    vector<int> a1{1, 3, 5, 7, 9};
    vector<int> a2{2, 4, 6, 8};
    list<pair<int,int>> r1;
    findSmallestPairs(r1, a1, a2, 5);
    cout << r1 << endl;

    vector<int> a3{4, 7, 9, 11, 20};
    vector<int> a4{8, 21, 35};
    list<pair<int,int>> r2;
    findSmallestPairs(r2, a3, a4, 12);
    cout << r2 << endl;
}
