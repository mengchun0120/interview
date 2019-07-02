#include <cassert>
#include <vector>
#include <iostream>
#include <list>

using namespace std;

/*
Given the in-order and post-order traversal of a binary tree, construct
the binary tree.
*/

struct Node {
    int m_val;
    Node *m_left, *m_right;

    Node(int val)
    : m_val(val)
    , m_left(nullptr)
    , m_right(nullptr)
    {
    }
};

Node *constructBinaryTree(const vector<int>& inOrder,
                          unsigned int inOrderStart,
                          unsigned int inOrderEnd,
                          const vector<int>& postOrder,
                          unsigned int postOrderStart,
                          unsigned int postOrderEnd)
{
    if(inOrderStart == inOrderEnd) {
        return nullptr;
    }

    int rootVal = postOrder[postOrderEnd-1];
    Node *root = new Node(rootVal);
    unsigned i;

    for(i = inOrderStart; i < inOrderEnd; ++i) {
        if(inOrder[i] == rootVal) {
            break;
        }
    }

    unsigned int j = postOrderStart + i - inOrderStart;

    root->m_left = constructBinaryTree(inOrder, inOrderStart, i,
                               postOrder, postOrderStart, j);

    root->m_right = constructBinaryTree(inOrder, i+1, inOrderEnd,
                               postOrder, j, postOrderEnd-1);

    return root;
}

Node *constructBinaryTree(const vector<int>& inOrder,
                          const vector<int>& postOrder)
{
    return constructBinaryTree(inOrder, 0, inOrder.size(),
                               postOrder, 0, postOrder.size());
}

void getInOrder(vector<int>& a, Node *tree)
{
    list<Node *> stack;
    size_t i = 0;
    Node *p;

    p = tree;
    while(p != nullptr) {
        stack.push_back(p);
        p = p->m_left;
    }

    while(stack.size() > 0) {
        p = stack.back();
        a[i++] = p->m_val;
        stack.pop_back();

        if(p->m_right != nullptr) {
            p = p->m_right;
            while(p != nullptr) {
                stack.push_back(p);
                p = p->m_left;
            }
        }
    }
}

void getPostOrder(vector<int>& a, Node *tree)
{
    list<Node *> stack;
    size_t i = 0;
    Node *p = tree;

    while(p != nullptr) {
        stack.push_back(p);
        if(p->m_left != nullptr) {
            p = p->m_left;
        } else {
            p = p->m_right;
        }
    }

    while(stack.size() > 0) {
        p = stack.back();
        a[i++] = p->m_val;
        stack.pop_back();

        if(stack.size() > 0) {
            Node *pr = stack.back();
            if(p == pr->m_left && pr->m_right != nullptr) {
                p = pr->m_right;
                while(p != nullptr) {
                    stack.push_back(p);
                    if(p->m_left != nullptr) {
                        p = p->m_left;
                    } else {
                        p = p->m_right;
                    }
                }
            }
        }
    }
}

template <typename T>
bool operator==(const vector<T>& a1, const vector<T>& a2)
{
    if(a1.size() != a2.size()) {
        return false;
    }

    for(size_t i = 0; i < a1.size(); ++i) {
        if(a1[i] != a2[i]) {
            return false;
        }
    }

    return true;
}

template <typename T>
ostream& operator<<(ostream& os, const vector<T>& a)
{
    os << '[';
    size_t sz = a.size();
    if(sz > 0) {
        os << a[0];
        for(size_t i = 1; i < sz; ++i) {
            os << ',' << a[i];
        }
    }
    os << ']';
    return os;
}

void test(int idx, const vector<int>& inOrder, const vector<int>& postOrder)
{
    cout << "test " << idx << endl;

    Node *tree = constructBinaryTree(inOrder, postOrder);
    vector<int> inOrder1(inOrder.size());
    vector<int> postOrder1(postOrder.size());

    getInOrder(inOrder1, tree);
    getPostOrder(postOrder1, tree);

    assert(inOrder == inOrder1);
    assert(postOrder == postOrder1);
}

int main(int argc, const char *argv[])
{
    vector<int> inOrder0{1, 0, 2};
    vector<int> postOrder0{1, 2, 0};

    test(0, inOrder0, postOrder0);

    vector<int> inOrder1{5, 3, 6, 1, 7, 4, 8, 0, 9, 2, 10};
    vector<int> postOrder1{5, 6, 3, 7, 8, 4, 1, 9, 10, 2, 0};

    test(1, inOrder1, postOrder1);
}

