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

    ~Twitter();

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
    int parent = (i - 1) / 2;

    while(parent >= 0) {
        HeapRecord& p = heap[parent];
        if(p.it->time >= r.it->time)
            break;

        heap[i] = p;
        i = parent;
        parent = (i - 1) / 2;
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
                maxTime = right.it->time;
            }
        }

        if(maxIdx == i)
            break;

        heap[i] = heap[maxIdx];
        leftIdx = 2 * i + 1;
    }

    if(i != idx)
        heap[idx] = r;
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
}
