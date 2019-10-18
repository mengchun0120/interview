/*
Write a function to generate genrralized
abbreviation of a word.

Example
Input "word"
Output ["word", "1ord', "w1rd", "wo1d",
"wor1", "2rd", "w2d", "wo2", "1o1d", "1or1',
"w1r1", "3d", "w3", "4"]
*/

#include <cassert>
#include <string>
#include <list>
#include <vector>
#include <unordered_set>
#include <iostream>

using namespace std;

void print(const list<string>& p)
{
    auto it = p.begin();
    for(; it != p.end(); it++) {
        cout << '"' << *it << '"' << " ";
    }
    cout << endl;
}

void getAbbr(list<string>& abbrs,
             const string& s)
{
    unsigned int sz = s.size();
    if(sz == 0) {
        return;
    }

    vector<list<string>> m(sz);

    m[0].emplace_back(s.substr(0, 1));
    m[0].emplace_back("1");
    for(unsigned i = 1; i < sz; ++i) {
        m[i].emplace_back(to_string(i+1));

        auto it = m[i-1].begin();
        auto e = m[i-1].end();
        for(; it != e; ++it) {
            m[i].emplace_back(*it + s[i]);
        }

        for(unsigned j = 1; j <= i; ++j) {
            string p = to_string(j);
            list<string>& q = m[i-j];
            auto it1 = q.begin();
            auto e1 = q.end();
            for(; it1 != e1; ++it1) {
                string& t = *it1;
                char ch = t[t.size()-1];
                if(ch >= '0' && ch <= '9') {
                    continue;
                }
                m[i].emplace_back(t+p);
            }
        }
    }

    abbrs = move(m[sz-1]);
}

bool compare(const list<string>& r,
             const list<string>& e)
{
    if(r.size() != e.size()) {
        return false;
    }

    unordered_set<string> rs;
    auto rit = r.begin();
    auto rend = r.end();

    for(; rit != rend; rit++) {
        rs.insert(*rit);
    }

    unordered_set<string> es;
    auto eit = e.begin();
    auto eend = e.end();

    for(; eit != eend; eit++) {
        es.insert(*eit);
    }

    return rs == es;
}

int main()
{
    list<string> r1;
    list<string> e1{
        "word", "1ord", "w1rd", "wo1d",
        "wor1", "2rd", "w2d", "wo2",
        "1o1d", "1or1", "w1r1", "3d",
        "w3", "4", "2r1", "1o2"
    };
    string w1 = "word";
    getAbbr(r1, w1);
    assert(compare(r1, e1));
}
