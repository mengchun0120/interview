#include <cassert>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
Given a collection of intervals, merge all overlapping intervals. For example,
Given [1,3][2,6][8,10][15,18], return [1,6][8,10][15,18]
*/

struct Interval {
    int m_start, m_end;
};

ostream& operator<<(ostream& os, const Interval& i)
{
    os << '[' << i.m_start << ',' << i.m_end << ']';
    return os;
}

bool operator==(const Interval& i1, const Interval& i2)
{
    return i1.m_start == i2.m_start && i1.m_end == i2.m_end;
}

void mergeIntervals(vector<Interval>& result, const vector<Interval>& intervals)
{
    auto comp = [](const Interval& i1, const Interval& i2)->bool {
        return i1.m_start < i2.m_start;
    };

    vector<Interval> temp(intervals.size());

    copy(intervals.begin(), intervals.end(), temp.begin());
    sort(temp.begin(), temp.end(), comp);

    size_t sz = intervals.size();
    Interval intv = temp[0];

    for(size_t i = 1; i < sz; ++i) {
        if(temp[i].m_start <= intv.m_end) {
            if(temp[i].m_end > intv.m_end) {
                intv.m_end = temp[i].m_end;
            }
        } else {
            result.push_back(intv);
            intv = temp[i];
        }
    }

    result.push_back(intv);
}

bool checkResult(const vector<Interval>& r, const vector<Interval>& e)
{
    if(r.size() != e.size()) {
        return false;
    }

    for(auto it = r.begin(); it != r.end(); ++it) {
        auto it1 = find(e.begin(), e.end(), *it);
        if(it1 == e.end()) {
            return false;
        }
    }

    for(auto it = e.begin(); it != e.end(); ++it) {
        auto it1 = find(r.begin(), r.end(), *it);
        if(it1 == e.end()) {
            return false;
        }
    }

    return true;
}

int main()
{
    vector<Interval> i1{{2,3},{4,8},{1,7}};
    vector<Interval> e1{{1,8}};
    vector<Interval> r1;

    mergeIntervals(r1, i1);
    assert(checkResult(r1, e1));

    vector<Interval> i2{{1,3},{5,6},{2,4},{4,5},{11,12},{9,11}};
    vector<Interval> e2{{1,6},{9,12}};
    vector<Interval> r2;

    mergeIntervals(r2, i2);
    assert(checkResult(r2, e2));
}
