#include <cassert>
#include <cstring>
#include <iostream>
#include <unordered_map>

// Given a string, check if it is can be reorganized such that the same char is
// not next to each other, If possible, output a possible result. Example,
// input: google, one possible output: gogole
bool removeNeighborDuplicateByReordering(char* str, int len)
{
    if(len < 1) {
        return true;
    }

    int dupStart = -1;
    char tmp;

    for(int i = 1; i < len; ++i) {
        if(str[i] != str[i-1]) {
            if(dupStart >= 0) {
                tmp = str[i];
                str[i] = str[dupStart+1];
                str[dupStart+1] = tmp;
                dupStart += 2;
                if(dupStart >= i-1) {
                    dupStart = -1;
                }
            }
        } else {
            if(dupStart == -1) {
                dupStart = i-1;
            }

            int j;
            for(j = dupStart-1; j >= 0; --j) {
                if((j == 0 || str[j-1] != str[i]) &&
                   (j == dupStart-1 || str[j+1] != str[i])) {
                    break;
                }
            }

            if(j >= 0) {
                tmp = str[i];
                str[i] = str[dupStart+1];
                str[dupStart+1] = tmp;
                dupStart += 2;
                if(dupStart >= i) {
                    dupStart = -1;
                }
            }
        }
    }

    return dupStart == -1;
}

bool hasSameChars(const char *s1, const char *s2, int len)
{
    std::unordered_map<char,int> charMap1, charMap2;
    std::unordered_map::iterator it1, it2;
    int i;

    for(i = 0; i < len; ++i) {
        it1 = charMap1.find(s1[i]);
        if(it1 != charMap1.end()) {
            it1->second++;
        } else {
            charMap1[s1[i]] = 1;
        }

        it2 = charMap2.find(s2[i]);
        if(it2 != charMap2.end()) {
            it2->second++;
        } else {
            charMap2[s2[i]] = 1;
        }
    }

    for(it1 = charMap1.begin(); it1 != charMap1.end(); ++it1) {
        it2 = charMap2.find(it1->first);
        if(it2 == charMap2.end() || it1->second != it2->second) {
            return false;
        }
    }

    for(it2 = charMap2.begin(); it2 != charMap2.end(); ++it2) {
        it1 = charMap1.find(it2->first);
        if(it1 == charMap1.end() || it1->second != it2->second) {
            return false;
        }
    }

    return true;
}

bool hasNeighborDuplicate(const char* str, int len)
{
    for(int i = 0; i < len-1; ++i) {
        if(str[i] == str[i+1]) {
            return true;
        }
    }
    return false;
}

void test(const char *str, bool expect_result)
{
    int len = strlen(str);
    char str_copy[len+1];
    strcpy(str_copy, str);
    bool ret = removeNeighborDuplicateByReordering(str_copy, len);
    assert(ret == expect_result);
    if(expect_result) {
        assert(hasSameChars(str, str_copy));
        assert(!hasNeighborDuplicate(str_copy, len));
    }
}

int main(int argc, char* argv[])
{
    char s0[] = "";
    test(s0, true);

    char s1[] = "aabaaaacbbc";
    test(s1, true);

    char s2[] = "aaaaaabbbbb";
    test(s2, true);

    char s3[] = "aaaabbbccc";
    test(s3, true);
}
