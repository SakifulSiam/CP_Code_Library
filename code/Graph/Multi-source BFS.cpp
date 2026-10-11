// WHEN: shortest unweighted distance from the nearest source. TIME: O(V+E).
// Initialize every source at distance 0 before starting BFS.
vector<int> multiSourceBFS(const vector<vector<int>>& g, vector<int> sources) {
    vector<int> dist(g.size(), -1);
    queue<int> q;
    for (int s : sources) if (dist[s] == -1) dist[s] = 0, q.push(s);
    while (!q.empty()) {
        int v = q.front(); q.pop();
        for (int to : g[v]) if (dist[to] == -1) {
            dist[to] = dist[v] + 1;
            q.push(to);
        }
    }
    return dist;
}
