#include <cassert>
#include <vector>
#include <iostream>

using namespace std;

/*
Sort an array of integers, where the final position of each element is at most
k steps away from its origin position.
*/

class Heap {
    vector<int> m_heap;
    unsigned int m_numElems;

public:
    Heap(unsigned size);

    virtual ~Heap();

    bool add(int i);

    bool getMin(int& i) const;

    unsigned int size() const
    {
        return m_numElems;
    }

    bool pop();

    const vector<int>& heap() const
    {
        return m_heap;
    }
};

Heap::Heap(unsigned size)
: m_heap(size)
, m_numElems(0)
{
}

Heap::~Heap()
{
}

bool Heap::add(int i)
{
    if(m_heap.size() == m_numElems) {
        return false;
    }

    unsigned int p = m_numElems;
    unsigned int parent = (p - 1) >> 1;

    while(p > 0 && m_heap[parent] > i) {
        m_heap[p] = m_heap[parent];
        p = parent;
        parent = (p - 1) >> 1;
    }

    m_heap[p] = i;
    ++m_numElems;

    return true;
}

bool Heap::getMin(int& i) const
{
    if(m_numElems == 0) {
        return false;
    }

    i = m_heap[0];
    return true;
}

bool Heap::pop()
{
    if(m_numElems == 0) {
        return false;
    } else if(m_numElems == 1) {
        --m_numElems;
        return true;
    }

    m_heap[0] = m_heap[m_numElems - 1];
    --m_numElems;

    unsigned int p = 0, minIdx;
    int i = m_heap[0], minElem;
    unsigned int leftChild, rightChild;

    while(true) {
        minElem = i;
        minIdx = p;

        leftChild = (p << 1) + 1;
        if(leftChild >= m_numElems) {
            break;
        }

        if(m_heap[leftChild] < minElem) {
            minElem = m_heap[leftChild];
            minIdx = leftChild;
        }

        rightChild = leftChild + 1;
        if(rightChild < m_numElems && m_heap[rightChild] < minElem) {
            minIdx = rightChild;
        }

        if(minIdx == p) {
            break;
        }

        m_heap[p] = m_heap[minIdx];
        p = minIdx;
    }

    m_heap[p] = i;

    return true;
}

ostream& operator<<(ostream& os, const Heap& h)
{
    os << '[';

    const vector<int>& a = h.heap();
    size_t sz = h.size();

    if(sz > 0) {
        os << a[0];
        for(size_t i = 1; i < sz; ++i) {
            os << ',' << a[i];
        }
    }

    os << ']';

    return os;
}

namespace std {

template<typename T>
ostream& operator<<(ostream& os, const vector<T>& a)
{
    os << '[';
    size_t sz = a.size();
    if(sz > 0) {
        os << a[0];
        for(size_t i = 1; i < sz; ++i) {
            os << ',' << a[i];
        }
    }
    os << ']';
    return os;
}

template<typename T>
bool operator==(const vector<T>& a1, const vector<T>& a2)
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

void sort(vector<int>& arr, unsigned int k)
{
    Heap h(2*k);

    unsigned int i, dst = 0;
    unsigned int sz = arr.size();

    // Initialize the heap with the first k elements
    for(i = 0; i < sz && i < k; ++i) {
        h.add(arr[i]);
    }

    while(i < sz) {
        // Add k elements to the heap
        for(unsigned int j = 0; i < sz && j < k; ++i, ++j) {
            h.add(arr[i]);
        }

        // Extract k elements from the heap
        for(unsigned int r = k; r > 0; --r, ++dst) {
            h.getMin(arr[dst]);
            h.pop();
        }
    }

    // Extract the remaining elements from the heap
    for(; h.size() > 0; ++dst) {
        h.getMin(arr[dst]);
        h.pop();
    }
}

int main(int argc, char *argv[])
{
    vector<int> a1{1, 0, 2, 3, 5, 6, 4};
    vector<int> r1{0, 1, 2, 3, 4, 5, 6};
    sort(a1, 2);
    assert(a1 == r1);

    :w

}

