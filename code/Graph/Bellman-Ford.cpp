// Single-source shortest paths with negative edges. TIME: O(VE).
// Returns false iff a negative cycle is reachable from source.
struct Edge { int u, v; long long w; };
bool bellmanFord(int n, int source, const vector<Edge>& edges,
                 vector<long long>& dist) {
    const long long INF = (1LL << 60);
    dist.assign(n, INF); dist[source] = 0;
    for (int it = 0; it < n - 1; ++it) {
        bool changed = false;
        for (auto [u, v, w] : edges) if (dist[u] < INF && dist[v] > dist[u] + w)
            dist[v] = dist[u] + w, changed = true;
        if (!changed) break;
    }
    for (auto [u, v, w] : edges)
        if (dist[u] < INF && dist[v] > dist[u] + w) return false;
    return true;
}
