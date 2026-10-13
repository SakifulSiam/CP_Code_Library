// Palindromic Tree (Eertree): O(n) distinct palindromes, lengths, occurrences, and transitions.
#include <bits/stdc++.h>
using namespace std;

struct PalindromicTree {
    struct Node {
        int len, link;
        int next[26];
        int count = 0; // occurrence count after prop
        Node(int len, int link) : len(len), link(link) {
            memset(next, 0, sizeof(next));
        }
    };
    vector<Node> tree;
    string s;
    int last, sz;

    PalindromicTree(int maxLen = 1) {
        tree.emplace_back(0, 1);    // 0: even root (len 0)
        tree.emplace_back(-1, 1);   // 1: odd root (len -1)
        sz = 2; last = 0;
    }

    int getLink(int v, int pos) {
        while (pos - tree[v].len - 1 < 0 || s[pos - tree[v].len - 1] != s[pos])
            v = tree[v].link;
        return v;
    }

    void extend(int pos) {
        int cur = getLink(last, pos);
        int ch = s[pos] - 'a';
        if (!tree[cur].next[ch]) {
            int link = tree[getLink(tree[cur].link, pos)].next[ch];
            tree.emplace_back(tree[cur].len + 2, link ? link : 0);
            tree[cur].next[ch] = sz++;
        }
        last = tree[cur].next[ch];
        tree[last].count++;
    }

    void build(const string& str) {
        s = str;
        for (int i = 0; i < (int)s.size(); ++i) extend(i);
        // Propagate counts from longest to shortest
        for (int i = sz - 1; i >= 2; --i) tree[tree[i].link].count += tree[i].count;
    }
};
