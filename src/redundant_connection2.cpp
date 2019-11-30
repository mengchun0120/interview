/*
 In this problem, a rooted tree is a directed graph such that, there is exactly one node 
 (the root) for which all other nodes are descendants of this node, plus every node has 
 exactly one parent, except for the root node which has no parents.

The given input is a directed graph that started as a rooted tree with N nodes (with distinct 
values 1, 2, ..., N), with one additional directed edge added. The added edge has two different
vertices chosen from 1 to N, and was not an edge that already existed.

The resulting graph is given as a 2D-array of edges. Each element of edges is a pair [u, v] 
that represents a directed edge connecting nodes u and v, where u is a parent of child v.

Return an edge that can be removed so that the resulting graph is a rooted tree of N nodes. 
If there are multiple answers, return the answer that occurs last in the given 2D-array.

Example 1:

Input: [[1,2], [1,3], [2,3]]
Output: [2,3]
Explanation: The given directed graph will be like this:
  1
 / \
v   v
2-->3

Example 2:

Input: [[1,2], [2,3], [3,4], [4,1], [1,5]]
Output: [4,1]
Explanation: The given directed graph will be like this:
5 <- 1 -> 2
     ^    |
     |    v
     4 <- 3

Note:
The size of the input 2D-array will be between 3 and 1000.
Every integer represented in the 2D-array will be between 1 and N, where N is the size of 
the input array.
*/

#include <cassert>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <list>

using namespace std;

struct Node {
    list<int> inEdges;
    list<int> outEdges;
};

ostream& operator<<(ostream& os, const vector<int>& v)
{
    for(auto it = v.begin(); it != v.end(); ++it) {
        os << *it << ' ';
    }
    return os;
}

void removeOutEdge(Node &n, int head, const vector<vector<int>>& edges)
{
    auto e = n.outEdges.end();
    for(auto it = n.outEdges.begin(); it != e; ++it) {
        const vector<int>& edge = edges[*it];
        if(edge[1] == head) {
            n.outEdges.erase(it);
            return;
        }
    }
}

vector<int> findRedundantDirectedConnection(vector<vector<int>>& edges)
{
    int numNodes = static_cast<int>(edges.size());
    vector<Node> nodes(numNodes);

    for(int i = 0; i < numNodes; ++i) {
        int tail = edges[i][0];
        int head = edges[i][1];
        nodes[tail-1].outEdges.push_back(i);
        nodes[head-1].inEdges.push_back(i);
        if(nodes[head-1].inEdges.size() == 2) {
            return edges[i];
        }
    }

    unordered_set<int> remainNodes;

    for(int i = 1; i <= numNodes; ++i) {
        remainNodes.insert(i);
    }

    list<int> queue1, queue2;
    list<int> *q = &queue1;

    for(int i = 0; i < numNodes; ++i) {
        if(nodes[i].outEdges.size() == 0) {
            q->push_back(i+1);
        }
    }

    while(!q->empty()) {
        list<int> *p = (q == &queue1) ? &queue2 : &queue1;

        while(!q->empty()) {
            int n = q->front();
            q->pop_front();
            remainNodes.erase(n);
            int inEdgeIdx = nodes[n-1].inEdges.front();
            int tail = edges[inEdgeIdx][0];
            removeOutEdge(nodes[tail-1], n, edges);
            if(nodes[tail-1].outEdges.size() == 0) {
                p->push_back(tail);
            }
        }

        q = p;
    }

    int largestEdgeIdx = 0;

    for(auto it = remainNodes.begin(); it != remainNodes.end(); ++it) {
        int edgeIdx = nodes[*it-1].inEdges.front();
        if(edgeIdx > largestEdgeIdx) {
            largestEdgeIdx = edgeIdx;
        }
    }

    return edges[largestEdgeIdx];
}

int main()
{
    vector<vector<int>> edges1{{1,2}, {1,3}, {3,2}};
    vector<int> result1 = findRedundantDirectedConnection(edges1);
    cout << result1 << endl;

    vector<vector<int>> edges2{{1,2}, {1,3}, {2,4}, {2,5},
                               {3,5}, {6,7}, {7,5}};
    vector<int> result2 = findRedundantDirectedConnection(edges2);
    cout << result2 << endl;

    vector<vector<int>> edges3{{1,2}, {2,3}, {3,4}, {4,1}, {1,5},
                               {5,6}, {5,7}, {6,8}, {6,9}, {7,10}};
    vector<int> result3 = findRedundantDirectedConnection(edges3);
    cout << result3 << endl;
}
