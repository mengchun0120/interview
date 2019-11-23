#include <cassert>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

/*
Given a string that represents time like "15:31", find the next time that is
formed by the numbers in the string(a number can be used more than once).
For "15:31", the answer should be "15:33".
*/

using namespace std;

void splitTime(vector<string>& timeVec, const string& t)
{
    unsigned int prevDelim = -1;
    for(unsigned int i = 0; i < t.size(); ++i) {
        if(t[i] != ':') {
            continue;
        }

        string timePart = t.substr(prevDelim+1, i-prevDelim-1);
        timeVec.push_back(timePart);
        prevDelim = i;
    }

    string lastPart = t.substr(prevDelim+1, t.size()-prevDelim-1);
    timeVec.push_back(lastPart);
}

void findDigits(vector<char>& digits, const string& t)
{
    digits.push_back(t[0]);
    for(unsigned int i = 1; i < t.size(); ++i) {
        if(t[i] < '0' || t[i] > '9') {
            continue;
        }

        auto it = find(digits.begin(), digits.end(), t[i]);
        if(it == digits.end()) {
            digits.push_back(t[i]);
        }
    }
    sort(digits.begin(), digits.end());
}

bool findNextDigit(char& next, const vector<char>& digits, char c)
{
    if(c == digits.back()) {
        return false;
    }

    int i;
    for(i = static_cast<int>(digits.size()-1); i >= 0; --i) {
        if(c == digits[i]) {
            break;
        }
    }

    next = digits[i+1];
    return true;
}

bool findNextTimePart(string& nextTimePart, const string& timePart,
                      const vector<char>& digits, const string& max)
{
    int i;
    nextTimePart = timePart;
    for(i = static_cast<int>(timePart.size()-1); i >= 0; --i) {
        char nextDigit;
        if(findNextDigit(nextDigit, digits, timePart[i])) {
            nextTimePart[i] = nextDigit;
            break;
        }

        if(i > 0) {
            nextTimePart[i] = digits[0];
        } else {
            return false;
        }
    }

    return nextTimePart <= max;
}

void findMinTimePart(string& minTimePart, const vector<char>& digits)
{
    for(unsigned int i = 0; i < minTimePart.size(); ++i) {
        minTimePart[i] = digits[0];
    }
}

bool findNextTime(string& nextTime, const string& curTime)
{
    vector<char> digits;
    findDigits(digits, curTime);
    if(digits.size() == 1) {
        return false;
    }

    vector<string> timeVec;
    splitTime(timeVec, curTime);

    vector<string> maxTimes{"23", "59", "59"};

    for(int i = static_cast<int>(timeVec.size()-1); i >= 0; --i) {
        string nextTimePart;
        if(findNextTimePart(nextTimePart, timeVec[i], digits, maxTimes[i])) {
            timeVec[i] = nextTimePart;
            break;
        }

        findMinTimePart(timeVec[i], digits);
    }

    for(unsigned int i = 0; i < timeVec.size(); ++i) {
        nextTime += timeVec[i];
        if(i < timeVec.size()-1) {
            nextTime += ":";
        }
    }

    return true;
}

void test(int testIndex, const string& curTime, bool found,
          const string& expectedNextTime)
{
    string nextTime;
    bool ret = findNextTime(nextTime, curTime);

    assert(ret == found);

    if(found) {
        assert(nextTime == expectedNextTime);
    }

    cout << "test" << testIndex << " successful" << endl;
}

int main(int argc, char* argv[])
{
    cout << "Running 1_8 ..." << endl;

    test(1, "11:11:11", false, "");
    test(2, "03:03:03", true, "03:03:30");
    test(3, "12:59:59", true, "15:11:11");
    test(4, "23:58:59", true, "23:59:22");
    test(5, "23:59:59", true, "22:22:22");
}

