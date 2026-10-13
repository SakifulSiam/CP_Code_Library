// Mo's Algorithm on Tree: O((n + q) sqrt(n)) path queries on doubled Euler tour.
#include <bits/stdc++.h>
using namespace std;

struct TreeMo {
    struct Query { int l, r, lca, id; };
    int n, timer = 0;
    vector<vector<int>> g;
    vector<int> first, last, euler;
    TreeMo(int n) : n(n), g(n), first(n), last(n) { euler.reserve(2 * n); }
    void addEdge(int u, int v) { g[u].push_back(v); g[v].push_back(u); }
    void dfs(int v, int p) {
        first[v] = euler.size(); euler.push_back(v);
        for (int u : g[v]) if (u != p) dfs(u, v);
        last[v] = euler.size(); euler.push_back(v);
    }
    void build(int root = 0) { dfs(root, -1); }
    // If w is LCA: if w == u, query is [first[u], first[v]]; else [last[u], first[v]] + w
    Query makeQuery(int u, int v, int w, int id) const {
        if (first[u] > first[v]) swap(u, v);
        if (w == u) return {first[u], first[v], -1, id};
        return {last[u], first[v], w, id};
    }
    // Worked example: count distinct values on path u -> v
    vector<int> solve(vector<Query> qs, const vector<int>& val) const {
        int B = max(1, (int)(euler.size() / max(1.0, sqrt(qs.size()))));
        sort(qs.begin(), qs.end(), [&](const Query& a, const Query& b) {
            int ba = a.l / B, bb = b.l / B;
            return ba != bb ? ba < bb : ((ba & 1) ? a.r < b.r : a.r > b.r);
        });
        vector<int> ans(qs.size());
        vector<int> freq(1000005, 0);
        vector<char> active(n, 0);
        int distinct = 0, L = 0, R = -1;
        auto toggle = [&](int v) {
            active[v] ^= 1;
            int c = val[v];
            if (active[v]) { if (++freq[c] == 1) distinct++; }
            else { if (--freq[c] == 0) distinct--; }
        };
        for (auto& q : qs) {
            while (L > q.l) toggle(euler[--L]);
            while (R < q.r) toggle(euler[++R]);
            while (L < q.l) toggle(euler[L++]);
            while (R > q.r) toggle(euler[R--]);
            if (q.lca != -1) toggle(q.lca);
            ans[q.id] = distinct;
            if (q.lca != -1) toggle(q.lca);
        }
        return ans;
    }
};
