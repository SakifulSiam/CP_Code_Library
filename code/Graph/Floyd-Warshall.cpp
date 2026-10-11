// All-pairs shortest paths. TIME: O(n^3), SPACE: O(n^2).
// INF means unreachable. Handles negative edges, but not negative cycles.
using ll = long long;
const ll INF = (1LL << 60);
void floydWarshall(vector<vector<ll>>& d) {
    int n = (int)d.size();
    for (int k = 0; k < n; ++k)
        for (int i = 0; i < n; ++i) if (d[i][k] < INF)
            for (int j = 0; j < n; ++j) if (d[k][j] < INF)
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
}
// A negative cycle exists if d[v][v] < 0 after the algorithm.
