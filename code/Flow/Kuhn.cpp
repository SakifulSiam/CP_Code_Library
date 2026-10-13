// Kuhn's algorithm for maximum bipartite matching; left side vertices 0..n-1.
struct Kuhn {
    int n, m;
    vector<vector<int>> g;
    vector<int> matchRight, seen;
    int timer = 0;
    Kuhn(int n, int m) : n(n), m(m), g(n), matchRight(m, -1), seen(n) {}
    void addEdge(int left, int right) { g[left].push_back(right); }
    bool dfs(int v) {
        if (seen[v] == timer) return false;
        seen[v] = timer;
        for (int to : g[v]) if (matchRight[to] == -1 || dfs(matchRight[to])) { matchRight[to] = v; return true; }
        return false;
    }
    int maximumMatching() {
        int ans = 0;
        for (int v = 0; v < n; ++v) { ++timer; ans += dfs(v); }
        return ans;
    }
};
