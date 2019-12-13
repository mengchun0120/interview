/*
We are given the head node root of a binary tree, where additionally 
every node's value is either a 0 or a 1.

Return the same tree where every subtree (of the given tree) not 
containing a 1 has been removed.

(Recall that the subtree of a node X is X, plus every node that is a
descendant of X.)
*/

#include <cassert>
#include <iostream>
#include <list>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;

    TreeNode(int v)
    : val(v)
    , left(nullptr)
    , right(nullptr)
    {}
};

TreeNode *pruneTree(TreeNode *root)
{
    if(!root) {
        return nullptr;
    }

    list<TreeNode*> stack;
    TreeNode *n = root;

    while(n) {
        stack.push_back(n);
        if(n->left) {
            n = n->left;
        } else {
            n = n->right;
        }
    }

    while(true) {
        n = stack.back();
        stack.pop_back();

        if(stack.empty()) {
            if(n->val == 0 && n->left == nullptr && n->right == nullptr) {
                delete n;
                root = nullptr;
            }
            break;
        }

        TreeNode *parent = stack.back();
        bool isLeftChild = parent->left == n;

        if(n->val == 0 && n->left == nullptr && n->right == nullptr) {
            if(isLeftChild) {
                parent->left = nullptr;
            } else {
                parent->right = nullptr;
            }
            delete n;
        }

        if(isLeftChild && parent->right) {
            n = parent->right;
            while(n) {
                stack.emplace_back(n);
                if(n->left) {
                    n = n->left;
                } else {
                    n = n->right;
                }
            }
        }
    }

    return root;
}

void printTree(TreeNode *n)
{
    if(!n) {
        return;
    }

    cout << n->val;

    if(n->left) {
        cout << ' ' << n->left->val;
    } else {
        cout << " null";
    }

    if(n->right) {
        cout << ' ' << n->right->val;
    } else {
        cout << " null";
    }

    cout << endl;

    if(n->left) {
        printTree(n->left);
    }

    if(n->right) {
        printTree(n->right);
    }
}

int main()
{
    cout << "test1" << endl;
    TreeNode *n1 = new TreeNode(1);
    TreeNode *n2 = new TreeNode(0);
    n1->left = n2;
    TreeNode *r1 = pruneTree(n1);
    printTree(r1);

    cout << "test2" << endl;
    TreeNode *n3 = new TreeNode(1);
    TreeNode *n4 = new TreeNode(1);
    TreeNode *n5 = new TreeNode(1);
    TreeNode *n6 = new TreeNode(0);
    TreeNode *n7 = new TreeNode(0);
    TreeNode *n8 = new TreeNode(0);
    TreeNode *n9 = new TreeNode(0);
    n3->left = n4;
    n3->right = n6;
    n4->left = n5;
    n4->right = n7;
    n6->left = n8;
    n6->right = n9;
    TreeNode *r2 = pruneTree(n3);
    printTree(r2);

    cout << "test3" << endl;
    TreeNode *t1 = new TreeNode(0);
    TreeNode *t2 = new TreeNode(1);
    TreeNode *t3 = new TreeNode(1);
    TreeNode *t4 = new TreeNode(1);
    TreeNode *t5 = new TreeNode(0);
    TreeNode *t6 = new TreeNode(0);
    TreeNode *t7 = new TreeNode(0);
    TreeNode *t8 = new TreeNode(1);
    t1->left = t2;
    t1->right = t3;
    t2->left = t4;
    t2->right = t5;
    t3->left = t7;
    t3->right = t8;
    t5->left = t6;
    TreeNode *r3 = pruneTree(t1);
    printTree(r3);
}
