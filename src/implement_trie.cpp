/*
Implement a trie with insert, search and startsWith methods.
*/

#include <cassert>
#include <iostream>
#include <string>

using namespace std;

struct Node {
    char ch;
    bool hasEnd;
    Node *left, *right;

    Node(char c)
    : ch(c)
    , hasEnd(false)
    , left(nullptr)
    , right(nullptr)
    {}
};

class Trie {
public:
    Trie();

    ~Trie();

    void insert(const string& s);

    bool search(const string& s);

    bool startsWith(const string& s);

private:
    Node *root;
};

Trie::Trie()
: root(nullptr)
{
}

Trie::~Trie()
{
}

void Trie::insert(const string& s)
{
    int sz = s.size();
    Node *parent = nullptr;
    Node *cur = root;

    for(int i = 0; i < sz; ++i) {
        Node *n;
        for(n = cur; n; n = n->right) {
            if(n->ch == s[i])
                break;
        }

        if(!n) {
            n = new Node(s[i]);
            if(parent) {
                n->right = parent->left;
                parent->left = n;
            } else {
                n->right = root;
                root = n;
            }
        }

        if(i < sz - 1) {
            parent = n;
            cur = parent->left;
        } else {
            n->hasEnd = true;
        }
    }
}

bool Trie::search(const string& s)
{
    Node *n = root;
    int sz = s.size();

    for(int i = 0; i < sz; ++i) {
        for(; n; n = n->right) {
            if(n->ch == s[i])
                break;
        }

        if(!n) return false;

        if(i < sz - 1) {
            n = n->left;
        } else if(!n->hasEnd) {
            return false;
        }
    }

    return true;
}

bool Trie::startsWith(const string& s)
{
    Node *n = root;
    int sz = s.size();

    for(int i = 0; i < sz; ++i) {
        for(; n; n = n->right) {
            if(n->ch == s[i])
                break;
        }

        if(!n) return false;

        n = n->left;
    }

    return true;
}

int main()
{
    Trie trie;
    trie.insert("add");
    trie.insert("ace");
    trie.insert("bark");
    trie.insert("bart");
    trie.insert("coffee");
    trie.insert("coffin");
    assert(trie.search("add"));
    assert(trie.search("bark"));
    assert(trie.startsWith("ba"));
    assert(trie.startsWith("coff"));
    assert(!trie.search("adda"));
    assert(!trie.search("a"));
    assert(!trie.search("coffine"));
    assert(!trie.startsWith("ce"));
}

