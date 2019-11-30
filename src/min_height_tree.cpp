/*
For an undirected graph with tree characteristics, we can choose any node as the root. 
The result graph is then a rooted tree. Among all possible rooted trees, those with 
minimum height are called minimum height trees (MHTs). Given such a graph, write a
function to find all the MHTs and return a list of their root labels.

Format
The graph contains n nodes which are labeled from 0 to n - 1. You will be given the 
number n and a list of undirected edges (each edge is a pair of labels).

You can assume that no duplicate edges will appear in edges. Since all edges are 
undirected, [0, 1] is the same as [1, 0] and thus will not appear together in edges.

Example 1 :

Input: n = 4, edges = [[1, 0], [1, 2], [1, 3]]

        0
        |
        1
       / \
      2   3 

Output: [1]

Example 2 :

Input: n = 6, edges = [[0, 3], [1, 3], [2, 3], [4, 3], [5, 4]]

     0  1  2
      \ | /
        3
        |
        4
        |
        5 

Output: [3, 4]

Note:
    According to the definition of tree on Wikipedia: “a tree is an undirected graph 
    in which any two vertices are connected by exactly one path. In other words, any 
    connected graph without simple cycles is a tree.”
    The height of a rooted tree is the number of edges on the longest downward path 
    between the root and a leaf.
*/

#include <cassert>
#include <vector>
#include <list>
#include <iostream>
#include <unordered_set>
#include <utility>

using namespace std;

struct Node {
    list<int> neighbors;
    int height;

    Node()
    : height(0)
    {}
};

ostream& operator<<(ostream& os, const vector<int>& a)
{
    for(auto it = a.begin(); it != a.end(); ++it) {
        os << *it << ' ';
    }
    return os;
}

vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) 
{
    vector<Node> nodes(n);
    list<int> leaves;

    for(auto it = edges.begin(); it != edges.end(); ++it) {
        int n1 = (*it)[0];
        int n2 = (*it)[1];
        nodes[n1].neighbors.push_back(n2);
        nodes[n2].neighbors.push_back(n1);
    }

    for(int i = 0; i < n; ++i) {
        if(nodes[i].neighbors.size() == 1) {
            leaves.push_back(i);
        }
    }

    for(auto it = leaves.begin(); it != leaves.end(); ++it) {
        unordered_set<int> visited;
        list<pair<int,int>> q;
        q.emplace_back(*it, 0);
        visited.insert(*it);
        while(!q.empty()) {
            pair<int,int> &p = q.front();
            Node &n = nodes[p.first];
            auto e1 = n.neighbors.end();
            int dist = p.second + 1;
            for(auto it1 = n.neighbors.begin(); it1 != e1; ++it1) {
                if(visited.find(*it1) == visited.end()) {
                    visited.insert(*it1);
                    q.emplace_back(*it1, dist);
                    if(dist > nodes[*it1].height) {
                        nodes[*it1].height = dist;
                    }
                }
            }
            q.pop_front();
        }
    }

    int minHeight = n;
    for(int i = 0; i < n; ++i) {
        if(nodes[i].height < minHeight) {
            minHeight = nodes[i].height;
        }
    }

    vector<int> results;
    for(int i = 0; i < n; ++i) {
        if(nodes[i].height == minHeight) {
            results.emplace_back(i);
        }
    }

    return results;
}

int main()
{
    vector<vector<int>> tree1{{0,1}, {1,2}, {1,3}};
    vector<int> result1 = findMinHeightTrees(4, tree1);
    cout << result1 << endl;

    vector<vector<int>> tree2{{0,2}, {1,2}, {2,3}, {3,4}, {4,5}, {4,6}};
    vector<int> result2 = findMinHeightTrees(7, tree2);
    cout << result2 << endl;

    vector<vector<int>> tree3{{0,1}, {1,2}, {1,3}, {1,4}, {3,5}, {3,7},
                              {7,9}, {4,8}, {4,6}, {6,10}, {4,11}, {11,12}};
    vector<int> result3 = findMinHeightTrees(13, tree3);
    cout << result3 << endl;
}