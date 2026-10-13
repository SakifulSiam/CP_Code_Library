// Centroid Decomposition: O(n log n). Skeleton with worked example for path counting.
#include <bits/stdc++.h>
using namespace std;

struct CentroidDecomposition {
    int n; vector<vector<int>> g; vector<int> sub; vector<char> blocked;
    CentroidDecomposition(int n) : n(n), g(n), sub(n), blocked(n) {}
    void addEdge(int u, int v) { g[u].push_back(v); g[v].push_back(u); }
    int calcSize(int v, int p) {
        sub[v] = 1;
        for (int u : g[v]) if (u != p && !blocked[u]) sub[v] += calcSize(u, v);
        return sub[v];
    }
    int findCentroid(int v, int p, int total) {
        for (int u : g[v]) if (u != p && !blocked[u] && sub[u] > total / 2)
            return findCentroid(u, v, total);
        return v;
    }
    // Worked example: count pairs of nodes with distance == K
    long long ans = 0; int K; vector<int> cnt;
    void getDists(int v, int p, int d, vector<int>& cur) {
        if (d > K) return;
        cur.push_back(d);
        for (int u : g[v]) if (u != p && !blocked[u]) getDists(u, v, d + 1, cur);
    }
    void process(int c) {
        vector<int> modified; cnt[0] = 1; modified.push_back(0);
        for (int u : g[c]) if (!blocked[u]) {
            vector<int> cur; getDists(u, c, 1, cur);
            for (int d : cur) if (K >= d) ans += cnt[K - d];
            for (int d : cur) { cnt[d]++; modified.push_back(d); }
        }
        for (int d : modified) cnt[d] = 0; // reset freq array
    }
    void build(int entry = 0) {
        int total = calcSize(entry, -1), c = findCentroid(entry, -1, total);
        process(c);
        blocked[c] = 1;
        for (int u : g[c]) if (!blocked[u]) build(u);
    }
};
