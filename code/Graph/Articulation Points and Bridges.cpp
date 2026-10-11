// WHEN: find articulation vertices and bridges in an undirected graph. TIME: O(V+E). ASSUMES: edge IDs distinguish parallel edges.
// Undirected graph; handles parallel edges by tracking the parent edge ID.
struct LowLink {
    int n, timer = 0;
    vector<vector<pair<int,int>>> g;
    vector<int> tin, low;
    vector<char> articulation;
    vector<pair<int,int>> bridges;
    LowLink(int n) : n(n), g(n), tin(n, -1), low(n), articulation(n) {}
    void addEdge(int u, int v, int id) { g[u].push_back({v,id}); g[v].push_back({u,id}); }
    void dfs(int v, int parentEdge = -1) {
        tin[v] = low[v] = timer++;
        int children = 0;
        for (auto [to,id] : g[v]) {
            if (id == parentEdge) continue;
            if (tin[to] != -1) low[v] = min(low[v], tin[to]);
            else {
                dfs(to, id); low[v] = min(low[v], low[to]); ++children;
                if (low[to] > tin[v]) bridges.push_back({v,to});
                if (parentEdge != -1 && low[to] >= tin[v]) articulation[v] = true;
            }
        }
        if (parentEdge == -1 && children > 1) articulation[v] = true;
    }
    void run() { for (int v = 0; v < n; ++v) if (tin[v] == -1) dfs(v); }
};
