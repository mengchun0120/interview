#include <cassert>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <cstdlib>

using namespace std;

/*
Design a data structure that supports all following operations in average O(1)
time.

* insert(val): Inserts an item val to the set if not already present.
* remove(val): Removes an item val from the set if present.
* getRandom: Returns a random element from current set of elements. Each element
must have the same probablity of being returned.
*/

class Test {
    unordered_map<int,size_t> m_map;
    vector<int> m_arr;

public:
    Test();

    bool insert(int i);

    bool remove(int i);

    int getRandom() const;

    bool find(int i);
};

Test::Test()
: m_map()
, m_arr()
{
}

bool Test::insert(int i)
{
    auto it = m_map.find(i);
    if(it != m_map.end()) {
        return false;
    }
    m_map.emplace(i, m_arr.size());
    m_arr.push_back(i);
    return true;
}

bool Test::remove(int i)
{
    auto it = m_map.find(i);
    if(it == m_map.end()) {
        return false;
    }
    if(m_arr.size() > 1 && it->second < m_arr.size()-1) {
        auto it1 = m_map.find(m_arr.back());
        m_arr[it->second] = m_arr.back();
        it1->second = it->second;
    }
    m_arr.pop_back();
    m_map.erase(it);
    return true;
}

int Test::getRandom() const
{
    size_t idx = (rand() / RAND_MAX) * (m_arr.size() - 1);
    return m_arr[idx];
}

bool Test::find(int i)
{
    return m_map.find(i) != m_map.end();
}

int main()
{
    Test t;
    for(int i = 0; i < 100; ++i) {
        assert(t.insert(i));
    }

    for(int i = 0; i < 10; ++i) {
        assert(t.remove(i));
    }

    for(int i = 0; i < 100; ++i) {
        int j = t.getRandom();
        assert(j > 9 && j < 100);
    }
}

