// WHEN: LCA, ancestor checks, and subtree intervals. TIME: O(log n) per LCA/lift. ASSUMES: rooted tree with vertices 1..n; call dfs(root,0).
// Binary lifting LCA and Euler intervals for one rooted tree (vertices 1..n).
struct TreeQueries {
    int n, LOG, timer = 0;
    vector<vector<int>> g, up;
    vector<int> depth, tin, tout, euler, doubleEuler;
    TreeQueries(int n) : n(n), LOG(1), g(n+1), depth(n+1), tin(n+1), tout(n+1) {
        while ((1 << LOG) <= n) ++LOG;
        up.assign(LOG, vector<int>(n+1)); euler.reserve(n);
    }
    void addEdge(int u, int v) { g[u].push_back(v); g[v].push_back(u); }
    void dfs(int v, int p) {
        tin[v] = timer++; euler.push_back(v); doubleEuler.push_back(v);
        up[0][v] = p;
        for (int j = 1; j < LOG; ++j) up[j][v] = up[j-1][up[j-1][v]];
        for (int to : g[v]) if (to != p) { depth[to] = depth[v] + 1; dfs(to, v); }
        tout[v] = timer; doubleEuler.push_back(v);
    }
    int lift(int v, int k) const { for (int j = 0; j < LOG; ++j) if (k >> j & 1) v = up[j][v]; return v; }
    int lca(int a, int b) const {
        if (depth[a] < depth[b]) swap(a, b);
        a = lift(a, depth[a] - depth[b]);
        if (a == b) return a;
        for (int j = LOG - 1; j >= 0; --j) if (up[j][a] != up[j][b]) a = up[j][a], b = up[j][b];
        return up[0][a];
    }
    bool isAncestor(int a, int b) const { return tin[a] <= tin[b] && tout[b] <= tout[a]; }
};
