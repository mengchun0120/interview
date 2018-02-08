#include <cassert>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <locale>

/*
Check if the string is a pangram & print all the missing characters if the
string is not a pangram in sorted order.
*/

using namespace std;

bool checkPangram(vector<char>& missing, const string& str)
{
    unordered_set<char> foundChars;
    locale loc;

    for(unsigned int i = 0; i < str.size(); ++i) {
        char c = tolower(str[i], loc);
        foundChars.emplace(c);
    }

    if(foundChars.size() == static_cast<unsigned int>('z'-'a'+1)) {
        return true;
    }

    for(char c1 = 'a'; c1 <= 'z'; ++c1) {
        if(foundChars.find(c1) == foundChars.end()) {
            missing.push_back(c1);
        }
    }

    return false;
}

void test(int testIndex, const string& str, bool expectedAnswer,
          const string& expectedMissing)
{
    vector<char> missing;
    bool answer = checkPangram(missing, str);

    assert(answer == expectedAnswer);
    if(!expectedAnswer) {
        assert(missing.size() == expectedMissing.size());
        for(unsigned int i = 0; i < expectedMissing.size(); ++i) {
            auto it = find(missing.begin(), missing.end(), expectedMissing[i]);
            assert(it != missing.end());
        }
    } else {
        assert(missing.empty());
    }

    cout << "test" << testIndex << " successful" << endl;
}

int main(int argc, char* argv[])
{
    cout << "Running 1_10" << endl;

    int testIndex = 1;
    test(testIndex++, "", false, "abcdefghijklmnopqrstuvwxyz");
    test(testIndex++, "abccddeeAAAzz", false, "fghijklmnopqrstuvwxy");
    test(testIndex++, "ijkabchlmnopuvwzyxdefghhqrasctxxv", true, "");
}

