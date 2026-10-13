// DSU on Tree (Sack): O(n log n) subtree queries. Small-to-large subtree merging.
#include <bits/stdc++.h>
using namespace std;

// Worked example: count distinct colors in each vertex's subtree
struct DSUOnTree {
    int n;
    vector<vector<int>> g;
    vector<int> col, sub, heavy, ans, cnt;
    int distinct = 0;
    DSUOnTree(int n, const vector<int>& col)
        : n(n), g(n), col(col), sub(n), heavy(n, -1), ans(n), cnt(1000005, 0) {}
    void addEdge(int u, int v) { g[u].push_back(v); g[v].push_back(u); }
    void calcSize(int v, int p) {
        sub[v] = 1; int best = 0;
        for (int u : g[v]) if (u != p) {
            calcSize(u, v); sub[v] += sub[u];
            if (sub[u] > best) { best = sub[u]; heavy[v] = u; }
        }
    }
    void add(int v, int p, int delta) {
        if (delta == 1) { if (++cnt[col[v]] == 1) distinct++; }
        else { if (--cnt[col[v]] == 0) distinct--; }
        for (int u : g[v]) if (u != p) add(u, v, delta);
    }
    void dfs(int v, int p, bool keep) {
        for (int u : g[v]) if (u != p && u != heavy[v]) dfs(u, v, false);
        if (heavy[v] != -1) dfs(heavy[v], v, true);
        for (int u : g[v]) if (u != p && u != heavy[v]) add(u, v, +1);
        if (++cnt[col[v]] == 1) distinct++;
        ans[v] = distinct;
        if (!keep) add(v, p, -1);
    }
    void run(int root = 0) { calcSize(root, -1); dfs(root, -1, true); }
};
