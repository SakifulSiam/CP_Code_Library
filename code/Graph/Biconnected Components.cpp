// Vertex-biconnected edge blocks in an undirected graph. TIME: O(V+E).
// Edge IDs handle parallel edges; assumes no self-loops.
struct Biconnected {
    int n, timer = 0;
    vector<vector<pair<int,int>>> g;
    vector<int> tin, low, edgeStack;
    vector<char> articulation;
    vector<vector<int>> blocks;
    Biconnected(int n) : n(n), g(n), tin(n, -1), low(n), articulation(n) {}
    void addEdge(int u, int v, int id) { g[u].push_back({v,id}); g[v].push_back({u,id}); }
    void dfs(int v, int parentEdge = -1) {
        tin[v] = low[v] = timer++;
        int children = 0;
        for (auto [to, id] : g[v]) {
            if (id == parentEdge) continue;
            if (tin[to] == -1) {
                edgeStack.push_back(id); ++children; dfs(to, id);
                low[v] = min(low[v], low[to]);
                if (low[to] >= tin[v]) {
                    if (parentEdge != -1 || children > 1) articulation[v] = 1;
                    vector<int> block;
                    while (!edgeStack.empty()) {
                        int e = edgeStack.back(); edgeStack.pop_back();
                        block.push_back(e);
                        if (e == id) break;
                    }
                    blocks.push_back(move(block));
                }
            } else if (tin[to] < tin[v]) {
                edgeStack.push_back(id);
                low[v] = min(low[v], tin[to]);
            }
        }
    }
    void build() { for (int v = 0; v < n; ++v) if (tin[v] == -1) dfs(v); }
};
