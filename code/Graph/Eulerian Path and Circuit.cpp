// Undirected multigraph: Hierholzer's algorithm, O(V+E).
// Returns a vertex sequence using every edge once, or {} if impossible.
vector<int> eulerTrail(int n, const vector<pair<int,int>>& edges) {
    if (n == 0) return {};
    int m = edges.size();
    vector<vector<pair<int,int>>> g(n);
    vector<int> degree(n);
    for (int id = 0; id < m; ++id) {
        auto [u, v] = edges[id];
        g[u].push_back({v, id}); g[v].push_back({u, id});
        ++degree[u]; ++degree[v];
    }
    vector<int> odd;
    for (int v = 0; v < n; ++v) if (degree[v] & 1) odd.push_back(v);
    if (odd.size() != 0 && odd.size() != 2) return {};
    int start = odd.empty() ? 0 : odd[0];
    if (odd.empty()) for (int v = 0; v < n; ++v) if (degree[v]) { start = v; break; }
    vector<char> used(m);
    vector<int> it(n), st{start}, path;
    while (!st.empty()) {
        int v = st.back();
        while (it[v] < (int)g[v].size() && used[g[v][it[v]].second]) ++it[v];
        if (it[v] == (int)g[v].size()) path.push_back(v), st.pop_back();
        else {
            auto [to, id] = g[v][it[v]++];
            if (!used[id]) used[id] = 1, st.push_back(to);
        }
    }
    if ((int)path.size() != m + 1) return {};
    reverse(path.begin(), path.end());
    return path;
}
