#include <cassert>
#include <string>

/*
Implement wildcard pattern matching with support for '?' and '*'.
*/

using namespace std;

bool match(const string& pattern, const string& s)
{
    int pidx = 0, sidx = 0;
    int psz = pattern.size(), ssz = s.size();
    int prevStarIdx = -1;

    while(pidx < psz && sidx < ssz) {
        if(pattern[pidx] != '?' && pattern[pidx] != '*') {
            if(pattern[pidx] == s[sidx]) {
                ++pidx;
                ++sidx;
            } else if(prevStarIdx != -1) {
                pidx = prevStarIdx + 1;
                ++sidx;
            } else {
                return false;
            }
        } else if(pattern[pidx] == '?') {
            ++pidx;
            ++sidx;
        } else if(pidx == psz - 1) {
            return true;
        } else {
            prevStarIdx = pidx;
            ++pidx;
        }
    }

    return (sidx == ssz && pidx == psz) ||
           (sidx == ssz && pidx == psz - 1 && pattern[pidx] == '*');
}

int main()
{
    string p0 = "";
    assert(match(p0, "") == true);
    assert(match(p0, "abc") == false);

    string p1 = "abc";
    assert(match(p1, "abc") == true);
    assert(match(p1, "") == false);
    assert(match(p1, "adc") == false);

    string p2 = "a?c?dfgg?";
    assert(match(p2, "abcedfggg") == true);
    assert(match(p2, "adefgg") == false);
    assert(match(p2, "abcddfghk") == false);

    string p3 = "abc*";
    assert(match(p3, "abcdefgh") == true);
    assert(match(p3, "abc") == true);
    assert(match(p3, "abd") == false);
    assert(match(p3, "abdefg") == false);

    string p4 = "ab*cd*";
    assert(match(p4, "abgcd") == true);
    assert(match(p4, "abgeeff") == false);
    assert(match(p4, "abgeeffcdecaf") == true);
    assert(match(p4, "abcd") == true);
    assert(match(p4, "abefcgdcs") == false);

    string p5 = "*abcd*efg*hij";
    assert(match(p5, "") == false);
    assert(match(p5, "abcdefghij") == true);
    assert(match(p5, "efgabcdcccccccefgggggggzhij") == true);
    assert(match(p5, "abcdefgddddhijdddd") == false);
    assert(match(p5, "abcdsssssssssssssefghij") == true);
}
