/*
Given a string, we can shift each of its letter to its successive letter, for
example: "abc" -> "bcd". We can keep shifting which forms the sequence:

"abc"->"bcd"->...->"xyz"

Given a list of strings which contains only lowercase alphabets, group all
strings that belong to the same shifting sequence.
*/

#include <cassert>
#include <list>
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>

using namespace std;

string findFirst(const string& s)
{
    string r = s;
    char min = r[0];

    for(unsigned int i = 1; i < r.size(); ++i) {
        if(r[i] < min) {
            min = r[i];
        }
    }

    int dist = min - 'a';
    for(unsigned int i = 0; i < r.size(); ++i) {
        r[i] -= dist;
    }

    return r;
}

void groupStr(list<list<string>>& result, const vector<string>& s)
{
    unordered_map<string, list<string>> m;

    for(auto it = s.begin(); it != s.end(); ++it) {
        string r = findFirst(*it);
        m[r].emplace_back(*it);
    }

    for(auto it = m.begin(); it != m.end(); ++it) {
        result.emplace_back(move(it->second));
    }
}

void getMap(unordered_map<string, int>& map, const list<string>& r)
{
    for(auto rit = r.begin(); rit != r.end(); ++rit) {
        auto it = map.find(*rit);
        if(it == map.end()) {
            map[*rit] = 0;
        } else {
            map[*rit]++;
        }
    }
}

bool compare(const list<string>& r, const list<string>& e)
{
    unordered_map<string, int> rmap;
    getMap(rmap, r);

    unordered_map<string, int> emap;
    getMap(emap, e);

    return rmap == emap;
}

bool checkResult(const list<list<string>>& r, const list<list<string>>& e)
{
    if(r.size() != e.size()) {
        return false;
    }

    for(auto eit = e.begin(); eit != e.end(); eit++) {
        auto rit = r.begin();
        for(; rit != r.end(); ++rit) {
            if(compare(*rit, *eit)) {
                break;
            }
        }

        if(rit == r.end()) {
            return false;
        }
    }

    return true;
}

void print(const list<string>& r)
{
    for(auto rit = r.begin(); rit != r.end(); ++rit) {
        cout << '"' << *rit << "\" ";
    }
    cout << endl;
}

void print(const list<list<string>>& r)
{
    for(auto it = r.begin(); it != r.end(); ++it) {
        print(*it);
    }
}

int main()
{
    vector<string> s1{"abc", "cde", "ac", "wy", "ccf", "ffi"};
    list<list<string>> r1;
    list<list<string>> e1{
        {"abc", "cde"},
        {"ac", "wy"},
        {"ccf", "ffi"}
    };
    groupStr(r1, s1);
    assert(checkResult(r1, e1));
}
