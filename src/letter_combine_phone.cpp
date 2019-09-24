#include <cassert>
#include <list>
#include <vector>
#include <string>
#include <utility>
#include <unordered_set>

using namespace std;

/*
Given a digit string, return all possible letter combinations that the number
could represent. A mapping of digit to letters is given below:
2 -> a, b, c
3 -> d, e, f
4 -> g, h, i
5 -> j, k, l
6 -> m, n, o
7 -> p, q, r, s
8 -> t, u, v
9 -> w, x, y, z
 */

void getString(unordered_set<string>& result, const vector<char> *map,
               const vector<unsigned int>& off, const vector<unsigned int>& idx)
{
    unsigned int sz = off.size();
    string t(sz, ' ');

    for(unsigned int i = 0; i < sz; ++i) {
        t[i] = map[off[i]][idx[i]];
    }

    result.insert(std::move(t));
}

bool moveToNext(vector<unsigned int>& idx, const vector<unsigned int>& off,
                const vector<char> *map)
{
    unsigned int sz = idx.size();
    unsigned int i = 0;

    for(; i < sz; ++i) {
        if(idx[i] < map[off[i]].size() - 1) {
            break;
        }

        idx[i] = 0;
    }

    if(i < sz) {
        ++idx[i];
        return true;
    }

    return false;
}

bool getAllCombinations(unordered_set<string>& result, const string& s)
{
    static const vector<char> map[] = {
        {'a', 'b', 'c'},        // 2
        {'d', 'e', 'f'},        // 3
        {'g', 'h', 'i'},        // 4
        {'j', 'k', 'l'},        // 5
        {'m', 'n', 'o'},        // 6
        {'p', 'q', 'r', 's'},   // 7
        {'t', 'u', 'v'},        // 8
        {'w', 'x', 'y', 'z'}    // 9
    };

    unsigned int sz = s.size();
    vector<unsigned int> idx(sz, 0);
    vector<unsigned int> offset(sz);
    
    for(unsigned int i = 0; i < sz; ++i) {
        int j = s[i] - '2';
        if(j < 0 || j > 7) {
            return false;
        }
        offset[i] = j;
    }

    do {
        getString(result, map, offset, idx);
    } while(moveToNext(idx, offset, map));

    return true;
}

int main()
{
    string s1 = "23";
    unordered_set<string> e1{"ad", "ae", "af", "bd", "be", "bf", "cd", "ce",
                             "cf"};
    unordered_set<string> r1;

    getAllCombinations(r1, s1);
    assert(r1 == e1);

    string s2 = "946";
    unordered_set<string> e2{"wgm", "wgn", "wgo", "whm", "whn", "who",
                             "wim", "win", "wio", "xgm", "xgn", "xgo",
                             "xhm", "xhn", "xho", "xim", "xin", "xio",
                             "ygm", "ygn", "ygo", "yhm", "yhn", "yho",
                             "yim", "yin", "yio", "zgm", "zgn", "zgo",
                             "zhm", "zhn", "zho", "zim", "zin", "zio"};
    unordered_set<string> r2;

    getAllCombinations(r2, s2);
    assert(r2 == e2);
}