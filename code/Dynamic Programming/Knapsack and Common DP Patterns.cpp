// Tree Knapsack, Bounded Knapsack (Binary Splitting), Bitset Subset-Sum, and Space-Optimized Edit Distance
#include <bits/stdc++.h>
using namespace std;

// 1. Tree Knapsack: O(N * W) or O(N^2). Careful bounds iterate min(sub[u], W)
int n, W;
vector<vector<int>> g;
vector<int> sz, val, wt;
vector<vector<long long>> dp; // dp[u][w] = max value in subtree u with weight w
void treeKnapsack(int u, int p) {
    sz[u] = 1;
    dp[u].assign(W + 1, 0);
    if (wt[u] <= W) dp[u][wt[u]] = val[u];
    for (int v : g[u]) if (v != p) {
        treeKnapsack(v, u);
        vector<long long> next_dp = dp[u];
        for (int i = 0; i <= min(sz[u], W); ++i) {
            for (int j = 0; j <= min(sz[v], W - i); ++j) {
                next_dp[i + j] = max(next_dp[i + j], dp[u][i] + dp[v][j]);
            }
        }
        sz[u] += sz[v];
        dp[u] = move(next_dp);
    }
}

// 2. Bounded Knapsack with Binary Splitting: item with count C split into 1, 2, 4, ..., R
long long boundedKnapsack(const vector<int>& weights, const vector<long long>& values,
                        const vector<int>& counts, int capacity) {
    vector<long long> dp(capacity + 1, 0);
    for (size_t i = 0; i < weights.size(); ++i) {
        int c = counts[i], w = weights[i]; long long v = values[i];
        for (int k = 1; c > 0; k = min(2 * k, c)) {
            int cur_w = k * w; long long cur_v = k * v;
            for (int cap = capacity; cap >= cur_w; --cap)
                dp[cap] = max(dp[cap], dp[cap - cur_w] + cur_v);
            c -= k;
        }
    }
    return dp[capacity];
}

// 3. Bitset Subset-Sum: O(N * W / 64) reachability
bool subsetSumBitset(const vector<int>& a, int target) {
    bitset<1000005> bs;
    bs[0] = 1;
    for (int x : a) bs |= (bs << x);
    return bs[target];
}

// 4. Space-Optimized Edit Distance in O(N * M) time and O(M) memory
int editDistance(const string& s, const string& t) {
    int n = s.size(), m = t.size();
    vector<int> dp(m + 1);
    iota(dp.begin(), dp.end(), 0);
    for (int i = 1; i <= n; ++i) {
        int prev = dp[0];
        dp[0] = i;
        for (int j = 1; j <= m; ++j) {
            int temp = dp[j];
            if (s[i - 1] == t[j - 1]) dp[j] = prev;
            else dp[j] = 1 + min({prev, dp[j], dp[j - 1]});
            prev = temp;
        }
    }
    return dp[m];
}
