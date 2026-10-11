// Boolean clauses (x == xv) OR (y == yv). TIME: O(V+E).
struct TwoSAT {
    int n;
    vector<vector<int>> g, rg;
    vector<int> order, comp;
    vector<char> seen;
    TwoSAT(int n) : n(n), g(2*n), rg(2*n) {}
    int node(int x, bool value) { return 2*x + !value; }
    void implication(int a, int b) { g[a].push_back(b); rg[b].push_back(a); }
    void addOr(int x, bool xv, int y, bool yv) {
        int a = node(x, xv), b = node(y, yv);
        implication(a^1, b); implication(b^1, a);
    }
    void dfs1(int v) {
        seen[v] = 1;
        for (int to : g[v]) if (!seen[to]) dfs1(to);
        order.push_back(v);
    }
    void dfs2(int v, int c) { comp[v] = c; for (int to : rg[v]) if (comp[to] == -1) dfs2(to, c); }
    bool solve(vector<int>& value) {
        seen.assign(2*n, 0); order.clear();
        for (int v = 0; v < 2*n; ++v) if (!seen[v]) dfs1(v);
        comp.assign(2*n, -1);
        for (int i = 2*n-1, c = 0; i >= 0; --i)
            if (comp[order[i]] == -1) dfs2(order[i], c++);
        value.resize(n);
        for (int x = 0; x < n; ++x) {
            if (comp[2*x] == comp[2*x+1]) return false;
            value[x] = comp[2*x] > comp[2*x+1];
        }
        return true;
    }
};
