/*
Design a simplified version of Twitter where users can post tweets, follow
/unfollow another user and is able to see the 10 most recent tweets in the
user's news feed. Your design should support the following methods:

postTweet(userId, tweetId): Compose a new tweet.

getNewsFeed(userId): Retrieve the 10 most recent tweets in the user's news feed.
Each item in the news feed must be posted by users who the user followed or by
the user herself. Tweets must be ordered from the most recent to least recent.

follow(followerId, followeeId): Follower follows a followee.

unfollow(followerId, followeeId): Follower unfollows a followee.
*/

#include <cassert>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <list>

using namespace std;

struct Feed {
    int tweetId;
    long long time;

    Feed(int id, long long t);
};

Feed::Feed(int id, long long t)
: tweetId(id)
, time(t)
{}

struct UserRecord {
    unordered_set<int> followees;
    list<Feed> feeds;

    UserRecord()
    {}
};

ostream& operator<<(ostream& os, const Feed& f)
{
    os << "Feed(" << f.tweetId << ',' << f.time << ')';
    return os;
}

template <typename T>
ostream& operator<<(ostream& os, const vector<T>& v)
{
    os << '[';
    if(v.size() > 0) {
        os << v[0];
        for(unsigned int i = 1; i < v.size(); ++i) {
            os << ", " << v[i];
        }
    }
    os << ']';
    return os;
}

struct HeapRecord {
    list<Feed>* feeds;
    list<Feed>::iterator it;

    HeapRecord()
    : feeds(nullptr)
    {}

    HeapRecord(const HeapRecord& h)
    : feeds(h.feeds)
    , it(h.it)
    {}

    HeapRecord& operator=(const HeapRecord& h)
    {
        feeds = h.feeds;
        it = h.it;
        return *this;
    }
};

class Twitter {
public:
    Twitter();

    ~Twitter()
    {}

    void postTweet(int userId, int tweetId);

    void getNewsFeed(vector<int>& feeds, int userId);

    void follow(int followerId, int followeeId);

    void unfollow(int followerId, int followeeId);

private:
    void initHeap(vector<HeapRecord>& heap, int userId);

    void heapifyUp(vector<HeapRecord>& heap, int idx);

    void heapifyDown(vector<HeapRecord>& heap, int idx, int heapSize);

private:
    unordered_map<int, UserRecord> userMap;
    long long time;
};

Twitter::Twitter()
: time(0)
{}

void Twitter::postTweet(int userId, int tweetId)
{
    UserRecord& record = userMap[userId];
    record.feeds.emplace_front(tweetId, time++);
}

void Twitter::heapifyUp(vector<HeapRecord>& heap, int idx)
{
    HeapRecord r(heap[idx]);
    int i = idx;

    while(i > 0) {
        int parent = (i - 1) / 2;
        HeapRecord& p = heap[parent];

        if(p.it->time >= r.it->time)
            break;

        heap[i] = p;
        i = parent;
    }

    if(idx != i)
        heap[i] = r;
}

void Twitter::heapifyDown(vector<HeapRecord>& heap, int idx, int heapSize)
{
    HeapRecord r(heap[idx]);
    int i = idx;
    int leftIdx = 2 * i + 1;

    while(leftIdx < heapSize) {
        int maxIdx= i;
        int maxTime = r.it->time;

        HeapRecord& left = heap[leftIdx];
        if(left.it->time > maxTime) {
            maxIdx = leftIdx;
            maxTime = left.it->time;
        }

        int rightIdx = leftIdx + 1;
        if(rightIdx < heapSize) {
            HeapRecord& right = heap[rightIdx];
            if(right.it->time > maxTime) {
                maxIdx = rightIdx;
            }
        }

        if(maxIdx == i)
            break;

        heap[i] = heap[maxIdx];
        i = maxIdx;
        leftIdx = 2 * i + 1;
    }

    if(i != idx)
        heap[i] = r;
}

void Twitter::initHeap(vector<HeapRecord>& heap, int userId)
{
    UserRecord& record = userMap[userId];

    int heapSize = 0;
    if(record.feeds.size() > 0) {
        ++heapSize;
    }

    auto& followees = record.followees;
    for(auto it = followees.begin(); it != followees.end(); ++it) {
        UserRecord& r = userMap[*it];
        if(r.feeds.size() > 0) {
            ++heapSize;
        }
    }

    heap.resize(heapSize);

    if(record.feeds.size() > 0) {
        heap[0].feeds = &(record.feeds);
        heap[0].it = record.feeds.begin();
    }

    int i = 1;
    for(auto it = followees.begin(); it != followees.end(); ++it) {
        UserRecord& r = userMap[*it];
        if(r.feeds.size() > 0) {
            heap[i].feeds = &(r.feeds);
            heap[i].it = r.feeds.begin();
            heapifyUp(heap, i);
            ++i;
        }
    }
}

void Twitter::getNewsFeed(vector<int>& feeds, int userId)
{
    vector<HeapRecord> heap;
    initHeap(heap, userId);

    int heapSize = heap.size();
    if(heapSize == 0)
        return;

    while(true) {
        HeapRecord& h = heap[0];

        feeds.push_back(h.it->tweetId);
        if(feeds.size() == 10)
            return;

        ++(h.it);
        if(h.it == h.feeds->end()) {
            if(heapSize == 1)
                return;

            heap[0] = heap[heapSize-1];
            --heapSize;
        }

        heapifyDown(heap, 0, heapSize);
    }
}

void Twitter::follow(int followerId, int followeeId)
{
    UserRecord& record = userMap[followerId];
    record.followees.insert(followeeId);
}

void Twitter::unfollow(int followerId, int followeeId)
{
    UserRecord& record = userMap[followerId];
    record.followees.erase(followeeId);
}

int main()
{
    Twitter twitter;
    twitter.postTweet(1, 8);
    twitter.postTweet(1, 9);
    twitter.postTweet(2, 10);
    twitter.postTweet(2, 11);
    twitter.postTweet(3, 12);
    twitter.postTweet(3, 13);
    twitter.postTweet(4, 5);
    twitter.postTweet(4, 6);
    twitter.postTweet(5, 7);
    twitter.postTweet(5, 1);
    twitter.postTweet(6, 2);
    twitter.postTweet(7, 3);
    twitter.postTweet(7, 4);
    twitter.postTweet(8, 14);
    twitter.postTweet(8, 15);
    twitter.follow(1, 2);
    twitter.follow(1, 3);
    twitter.follow(1, 4);

    vector<int> feeds1;
    twitter.getNewsFeed(feeds1, 1);
    cout << feeds1 << endl;

    twitter.follow(1, 5);
    twitter.follow(1, 6);
    twitter.follow(1, 7);

    vector<int> feeds2;
    twitter.getNewsFeed(feeds2, 1);
    cout << feeds2 << endl;

    twitter.follow(8, 1);
    twitter.follow(8, 2);
    twitter.follow(8, 7);
    twitter.follow(8, 6);
    twitter.follow(8, 5);
    twitter.follow(8, 3);

    vector<int> feeds3;
    twitter.getNewsFeed(feeds3, 8);
    cout << feeds3 << endl;
}
