/*
Given a non-empty binary search tree and a target value, find k values in the
BST that are closest to the target.

Note:
Given target value is a floating point. You may assume k is always valid, that
is: k <= total nodes. You are guanranteed to have only one unique set of k
values in the BST that are closest to the target.

Example:
Input: root = [4, 2, 5, 1, 3], target=3.714286, and k=2
    4
   / \
  2   5
 / \
1   3
Output: [4,3]

Follow up: Assume that the BST is balanced, could you solve it in less than
O(n) runtime where n=total nodes?
*/

#include <cassert>
#include <vector>
#include <list>
#include <iostream>

using namespace std;

struct Node {
    int val;
    Node *left, *right;

    Node()
    : left(nullptr)
    , right(nullptr)
    {}

    Node(int v)
    : val(v)
    , left(nullptr)
    , right(nullptr)
    {}

    ~Node()
    {}
};

double dist(int a, double b)
{
    double d = (double)a - b;
    if(d >= 0) {
        return d;
    }
    return -d;
}

ostream& operator<<(ostream& os, const Node& n)
{
    os << n.val << ':';
    if(n.left) {
        os << n.left->val << ':';
    } else {
        os << "n:";
    }
    if(n.right) {
        os << n.right->val;
    } else {
        os << "n:";
    }
    return os;
}

void printResult(const list<int>& r)
{
    for(auto it = r.begin(); it != r.end(); ++it) {
        cout << *it << ' ';
    }
    cout << endl;
}

void printStack(const list<const Node*>& s)
{
    for(auto it = s.begin(); it != s.end(); ++it) {
        cout << **it << ' ';
    }
    cout << endl;
}

void findClosest(list<int>& result, const Node *root, double val,
                 unsigned int k)
{
    list<const Node*> stack;
    const Node *n;

    n = root;
    while(n->left){
        stack.push_back(n);
        n = n->left;
    }

    while(n) {
        if(result.size() < k) {
            result.push_back(n->val);
        } else if(val <= result.front()) {
            break;
        } else if(dist(n->val, val) < dist(result.front(), val)) {
            result.pop_front();
            result.push_back(n->val);
        } else {
            break;
        }

        if(n->right) {
            n = n->right;
            while(n->left) {
                stack.push_back(n);
                n = n->left;
            }
        } else {
            while(stack.size() > 0 && stack.back()->right == n) {
                n = stack.back();
                stack.pop_back();
            }

            if(stack.size() > 0) {
                n = stack.back();
                stack.pop_back();
            } else {
                break;
            }
        }
    }
}

int main()
{
/*
    4
   / \
  2   5
 / \
1   3
*/
    Node nodes1[] = {Node(1), Node(2), Node(3), Node(4), Node(5)};
    nodes1[1].left = &nodes1[0];
    nodes1[1].right = &nodes1[2];
    nodes1[3].left = &nodes1[1];
    nodes1[3].right = &nodes1[4];

    list<int> r1;
    findClosest(r1, &nodes1[3], 3.5, 2);
    printResult(r1);

    list<int> r2;
    findClosest(r2, &nodes1[3], 2.1, 3);
    printResult(r2);

    list<int> r3;
    findClosest(r3, &nodes1[3], 3.7, 3);
    printResult(r3);

/*
         7
        / \
       5   8
      / \   \
     3   6   9
    / \
   2   4
  /
 1
*/
    Node nodes2[] = {Node(1), Node(2), Node(3), Node(4), Node(5), Node(6),
                     Node(7), Node(8), Node(9)};
    nodes2[1].left = &nodes2[0];
    nodes2[2].left = &nodes2[1];
    nodes2[2].right = &nodes2[3];
    nodes2[4].left = &nodes2[2];
    nodes2[4].right = &nodes2[5];
    nodes2[6].left = &nodes2[4];
    nodes2[6].right = &nodes2[7];
    nodes2[7].right = &nodes2[8];

    list<int> r4;
    findClosest(r4, &nodes2[6], 7.9, 3);
    printResult(r4);

    list<int> r5;
    findClosest(r5, &nodes2[6], 4.2, 5);
    printResult(r5);
}
