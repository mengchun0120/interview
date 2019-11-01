/*
Given a data stream input of non-negative integers a1, a2, ..., an, ...,
summarize the numbers seen so far as a list of disjoint intervals. For example,
suppose the integers from the data stream are 1, 3, 7, 2, 6, ..., then the
summary will be:
[1,1]
[1,1][3,3]
[1,1][3,3][7,7]
[1,3][7,7]
[1,3][6,7]
Follow up:
What if there are lots of merges and the number of disjoint intervals are small
compared to the data stream's size?
*/

#include <cassert>
#include <vector>
#include <iostream>
#include <list>
#include <utility>

using namespace std;

struct Node {
    int low, high;
    Node *left, *right;

    Node(int l, int h)
    : low(l)
    , high(h)
    , left(nullptr)
    , right(nullptr)
    {}
};

ostream& operator<<(ostream& os, const pair<int,int>& p)
{
    os << '(' << p.first << ',' << p.second << ')';
    return os;
}

ostream& operator<<(ostream& os, const vector<pair<int,int>>& s)
{
    os << '[';
    if(s.size() > 0) {
        os << s[0];
        for(unsigned int i = 1; i < s.size(); ++i) {
            os << ", " << s[i];
        }
    }
    os << ']';
    return os;
}

class DataStreamSummarizer {
public:
    DataStreamSummarizer();

    ~DataStreamSummarizer();

    void feed(int v);

    void getSummary(vector<pair<int,int>>& intervals);

private:
    void tryMergeNext(list<Node*>& stack, Node *n);
    void tryMergePrev(list<Node*>& stack, Node *n);

private:
    Node *root;
    int numIntervals;
};

DataStreamSummarizer::DataStreamSummarizer()
: root(nullptr)
, numIntervals(0)
{
}

DataStreamSummarizer::~DataStreamSummarizer()
{
}

void DataStreamSummarizer::feed(int v)
{
    if(!root) {
        root = new Node(v, v);
        numIntervals = 1;
        return;
    }

    list<Node*> stack;
    Node *n = root;

    while(n) {
        if(v >= n->low && v <= n->high) {
            return;
        }

        if(v < n->low - 1) {
            stack.push_front(n);
            n = n->left;
       } else if(v == n->low - 1) {
            n->low = v;
            tryMergePrev(stack, n);
            return;
       } else if(v > n->high + 1) {
            stack.push_front(n);
            n = n->right;
        } else {
            n->high = v;
            tryMergeNext(stack, n);
            return;
        }
    }

    Node *parent = stack.front();

    n = new Node(v, v);
    if(v < parent->low) {
        parent->left = n;
    } else {
        parent->right = n;
    }

    ++numIntervals;
}

void DataStreamSummarizer::getSummary(vector<pair<int,int>>& intervals)
{
    list<Node*> stack;
    Node *n;

    n = root;
    while(n) {
        stack.push_front(n);
        n = n->left;
    }

    intervals.reserve(numIntervals);
    while(stack.size() > 0) {
        n = stack.front();
        stack.pop_front();

        intervals.emplace_back(n->low, n->high);

        if(n->right) {
            n = n->right;
            while(n) {
                stack.push_front(n);
                n = n->left;
            }
        } else {
            while(stack.size() > 0 && stack.front()->right == n) {
                n = stack.front();
                stack.pop_front();
            }
        }
    }
}

void DataStreamSummarizer::tryMergeNext(list<Node*>& stack, Node *n)
{
    if(n->right) {
        Node *p = n;
        Node *t = p->right;
        while(t->left) {
            p = t;
            t = t->left;
        }

        if(n->high + 1 < t->low)
            return;

        n->high = t->high;
        if(p->left == t) {
            p->left = t->right;
        } else {
            p->right = t->right;
        }

        delete t;
        --numIntervals;

    } else {
        Node *t = n;
        auto it = stack.begin();
        while(it != stack.end() && (*it)->right == t) {
            t = *it;
            it++;
        }

        if(it == stack.end() || n->high + 1 < (*it)->low)
            return;

        (*it)->low = n->low;

        Node *p = stack.front();
        if(p->right == n) {
            p->right = n->left;
        } else {
            p->left = n->left;
        }

        delete n;
        --numIntervals;
    }
}

void DataStreamSummarizer::tryMergePrev(list<Node*>& stack, Node *n)
{
    if(n->left) {
        Node *p = n;
        Node *t = n->left;
        while(t->right) {
            p = t;
            t = t->right;
        }

        if(t->high + 1 < n->low)
            return;

        n->low = t->low;
        if(p->right == t) {
            p->right = t->left;
        } else {
            p->left = t->left;
        }

        delete t;
        --numIntervals;
    } else {
        Node *t = n;
        auto it = stack.begin();
        while(it != stack.end() && (*it)->left == t) {
            t = *it;
            ++it;
        }

        if(it == stack.end() || (*it)->high + 1 < n->low)
            return;

        (*it)->high = n->high;

        Node *p = stack.front();
        if(p->left == n) {
            p->left = n->right;
        } else {
            p->right = n->right;
        }

        delete n;
        --numIntervals;
    }
}

void getIntervals(vector<pair<int,int>>& intervals, const vector<int>& stream)
{
    DataStreamSummarizer s;
    for(auto it = stream.begin(); it != stream.end(); ++it) {
        s.feed(*it);
    }
    s.getSummary(intervals);
}

int main()
{
    vector<int> s1{1, 3, 7, 2, 6};
    vector<pair<int,int>> i1;
    getIntervals(i1, s1);
    cout << i1 << endl;

    vector<int> s2{3, 8, 1, 7, 9, 11, 10, 2, 4, 20, 21, 23};
    vector<pair<int,int>> i2;
    getIntervals(i2, s2);
    cout << i2 << endl;
}
