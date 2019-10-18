/*
Given a pattern and a string str, find if
str follow the same pattern. Here follow
means full match such that there is a
bijection between a letter in the pattern
a word in str. You may assume str contain
letters separated by single space.

Example 1
pattern="abba", str="dog cat cat dog"
return true

Example 2
pattern="abba", str="dog fog dog fog"
return false
*/

#include <cassert>
#include <string>
#include <unordered_map>

using namespace std;

bool match(const string& p, const string& s)
{
    unsigned int pi, si;
    unsigned int psz = p.size();
    unsigned int ssz = s.size();
    unordered_map<char,string> psmap;
    unordered_map<string,char> spmap;

    pi = 0;
    si = 0;
    if(s[si] == ' ') {
        si++;
    }

    while(pi < psz && si < ssz) {
        unsigned int q = si;
        while(q < ssz && s[q] != ' ') {
            q++;
        }

        string w = s.substr(si, q - si);

        auto pit = psmap.find(p[pi]);
        auto sit = spmap.find(w);
        if(pit == psmap.end()) {
            if(sit != spmap.end()) {
                return false;
            }

            psmap[p[pi]] = w;
            spmap[w] = p[pi];
        } else {
            if(sit == spmap.end()) {
                return false;
            }

            if(pit->second != w ||
               sit->second != p[pi]) {
                return false;
            }
        }

        si = (q < ssz) ? q + 1 : ssz;
        pi++;
    }

    return si == ssz && pi == psz;
}

int main()
{
    string p1 = "abba";
    string s1 = "dog cat cat dog";
    assert(match(p1, s1));

    string s2 = "dog dog dog dog";
    assert(!match(p1, s2));

    string s3 = "dog cat";
    assert(!match(p1, s3));

    string s4 = "vg ac ac vg vg";
    assert(!match(p1, s4));
}
