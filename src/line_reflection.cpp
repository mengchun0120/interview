/*
Given n points on a 2D plane, find if there is such a line parallel to y-axis
that reflect the given points.

Example 1:
Input [[1,1],[-1,1]]
Output true

Example 2:
Input [[1,1],[-1,-1]]
Output false

Follow up:
Could you do better than O(n^2)?
*/

#include <cassert>
#include <vector>
#include <unordered_map>
#include <functional>

using namespace std;

struct Point {
    int x;
    int y;
};

struct HashKey {
    double dist;
    int y;

    bool operator==(const HashKey& k) const
    {
        return dist == k.dist && y == k.y;
    }
};

struct MyHash {
    static hash<int> intHash;
    static hash<double> doubleHash;

    size_t operator()(const HashKey& k) const
    {
        return doubleHash(k.dist) ^ intHash(k.y);
    }
};


hash<int> MyHash::intHash;
hash<double> MyHash::doubleHash;

struct ReflectionRecord {
    int leftCount, rightCount;

    ReflectionRecord()
    : leftCount(0)
    , rightCount(0)
    {}
};

typedef unordered_map<HashKey, ReflectionRecord, MyHash> ReflectionMap;

bool lineReflection(double& line, const vector<Point> points)
{
    unsigned int maxIdx, minIdx;

    maxIdx = 0;
    minIdx = 0;
    for(unsigned int i = 1; i < points.size(); ++i) {
        if(points[i].x > points[maxIdx].x) {
            maxIdx = i;
        }
        if(points[i].x < points[minIdx].x) {
            minIdx = i;
        }
    }

    if(points[minIdx].y != points[maxIdx].y)
        return false;

    double mid = (double)(points[minIdx].x + points[maxIdx].x) / 2.0;
    ReflectionMap reflectMap;

    for(unsigned int i = 0; i < points.size(); ++i) {
        double dist = points[i].x - mid;
        if(dist == 0.0)
            continue;

        double absDist = dist > 0.0 ? dist : -dist;
        HashKey key{absDist, points[i].y};
        ReflectionRecord& r = reflectMap[key];
        if(dist < 0.0) {
            ++(r.leftCount);
        } else {
            ++(r.rightCount);
        }
    }

    for(auto it = reflectMap.begin(); it != reflectMap.end(); ++it) {
        if(it->second.leftCount != it->second.rightCount)
            return false;
    }

    line = mid;
    return true;
}

int main()
{
    vector<Point> points1{{-1,1},{1,1}};
    double line1;
    bool r1 = lineReflection(line1, points1);
    assert(r1 && line1 == 0.0);

    vector<Point> points2{{-1,1},{1,2}};
    double line2;
    bool r2 = lineReflection(line2, points2);
    assert(!r2);

    vector<Point> points3{{-1,1},{1,1},{-5,10},{8,7},{-8,7},{5,10},{100,20},
                          {-100,20},{101,30},{102,40},{-101,30},{-102,40}};
    double line3;
    bool r3 = lineReflection(line3, points3);
    assert(r3 && line3 == 0.0);

    vector<Point> points4{{-1,1},{1,1},{-5,10},{8,7},{-8,7},{5,10},{100,20},
                          {-100,20},{101,30},{102,40},{-101,30},{-101,40}};
    double line4;
    bool r4 = lineReflection(line4, points4);
    assert(!r4);
}
