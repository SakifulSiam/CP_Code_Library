// Hungarian Algorithm: Minimum Weight Maximum Bipartite Matching on N x M matrix in O(N^2 * M).
// 1-indexed. Returns {min_cost, assignment} where assignment[i] is matched right vertex for left vertex i.
#include <bits/stdc++.h>
using namespace std;

const long long INF = 1e18;

pair<long long, vector<int>> hungarian(int n, int m, const vector<vector<long long>>& cost) {
    vector<long long> u(n + 1), v(m + 1);
    vector<int> p(m + 1), way(m + 1);
    for (int i = 1; i <= n; ++i) {
        p[0] = i;
        int j0 = 0;
        vector<long long> minv(m + 1, INF);
        vector<char> used(m + 1, false);
        do {
            used[j0] = true;
            int i0 = p[j0], j1 = 0;
            long long delta = INF;
            for (int j = 1; j <= m; ++j) {
                if (!used[j]) {
                    long long cur = cost[i0][j] - u[i0] - v[j];
                    if (cur < minv[j]) { minv[j] = cur; way[j] = j0; }
                    if (minv[j] < delta) { delta = minv[j]; j1 = j; }
                }
            }
            for (int j = 0; j <= m; ++j) {
                if (used[j]) { u[p[j]] += delta; v[j] -= delta; }
                else minv[j] -= delta;
            }
            j0 = j1;
        } while (p[j0] != 0);
        do {
            int j1 = way[j0];
            p[j0] = p[j1];
            j0 = j1;
        } while (j0);
    }
    vector<int> match(n + 1);
    for (int j = 1; j <= m; ++j) if (p[j] <= n) match[p[j]] = j;
    return {-v[0], match};
}
