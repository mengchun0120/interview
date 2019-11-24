/*
Given a complete binary tree, count the number of nodes.

Note:

Definition of a complete binary tree from Wikipedia:
In a complete binary tree every level, except possibly the last, is completely
filled, and all nodes in the last level are as far left as possible. It can 
have between 1 and 2h nodes inclusive at the last level h.

Example:

Input: 
    1
   / \
  2   3
 / \  /
4  5 6

Output: 6
*/

#include <cassert>
#include <iostream>
#include <list>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

struct StackNode {
    TreeNode *node;
    int level;

    StackNode(TreeNode *n, int l)
    : node(n)
    , level(l)
    {}
};

int countNodes(TreeNode *root)
{
    if(root == NULL) {
        return 0;
    }

    list<StackNode> stack;
    TreeNode *n = root;
    int secondToLastLevel = 0;

    while(n->left != NULL && n->left->left != NULL) {
        ++secondToLastLevel;
        stack.emplace_back(n->right, secondToLastLevel);
        n = n->left;
    }

    int lastLevelCount = 0;

    while(n->left != NULL) {
        ++lastLevelCount;
        if(n->right != NULL) {
            ++lastLevelCount;
        } else {
            break;
        }

        if(stack.size() == 0) {
            break;
        }

        int level = stack.back().level;
        n = stack.back().node;
        stack.pop_back();
        while(level < secondToLastLevel) {
            ++level;
            stack.emplace_back(n->right, level);
            n = n->left;
        }
    }

    return lastLevelCount + (1 << (secondToLastLevel + 1)) - 1;
}

int main()
{
    TreeNode n1(1), n2(2), n3(3), n4(4), n5(5), n6(6);
    n1.left = &n2;
    n1.right = &n3;
    n2.left = &n4;
    n2.right = &n5;
    n3.left = &n6;
    assert(countNodes(&n1) == 6);
}
