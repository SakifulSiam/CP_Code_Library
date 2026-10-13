// Implicit Treap (Cartesian Tree on Array): O(log n) split, merge, insert, erase, range reverse.
#include <bits/stdc++.h>
using namespace std;

static mt19937 treap_rng(1337);

struct Node {
    int val, prio, sz = 1;
    bool rev = false;
    Node *l = nullptr, *r = nullptr;
    Node(int val) : val(val), prio(treap_rng()) {}
};

int sz(Node* t) { return t ? t->sz : 0; }
void pull(Node* t) { if (t) t->sz = 1 + sz(t->l) + sz(t->r); }
void push(Node* t) {
    if (t && t->rev) {
        swap(t->l, t->r);
        if (t->l) t->l->rev ^= 1;
        if (t->r) t->r->rev ^= 1;
        t->rev = false;
    }
}

void split(Node* t, int k, Node*& l, Node*& r) { // l gets first k elements, r gets rest
    push(t);
    if (!t) { l = r = nullptr; return; }
    if (sz(t->l) >= k) {
        split(t->l, k, l, t->l);
        r = t;
    } else {
        split(t->r, k - sz(t->l) - 1, t->r, r);
        l = t;
    }
    pull(t);
}

void merge(Node*& t, Node* l, Node* r) {
    push(l); push(r);
    if (!l || !r) { t = l ? l : r; return; }
    if (l->prio > r->prio) {
        merge(l->r, l->r, r);
        t = l;
    } else {
        merge(r->l, l, r->l);
        t = r;
    }
    pull(t);
}

// Reverse range [ql, qr] (0-indexed)
void reverseRange(Node*& root, int ql, int qr) {
    Node *a, *b, *c;
    split(root, qr + 1, b, c);
    split(b, ql, a, b);
    if (b) b->rev ^= 1;
    merge(root, a, b);
    merge(root, root, c);
}

void inorder(Node* t, vector<int>& res) {
    if (!t) return;
    push(t);
    inorder(t->l, res);
    res.push_back(t->val);
    inorder(t->r, res);
}
