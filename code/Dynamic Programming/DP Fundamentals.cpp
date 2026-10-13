// State design: define what dp[...] means, transitions, base cases, and evaluation order.
// 0/1 knapsack: iterate capacity downward so each item is used at most once.
long long knapsack01(const vector<int>& w, const vector<long long>& val, int cap) {
    vector<long long> dp(cap + 1);
    for (int i = 0; i < (int)w.size(); ++i)
        for (int c = cap; c >= w[i]; --c) dp[c] = max(dp[c], dp[c-w[i]] + val[i]);
    return dp[cap];
}
// Real-valued DP: use double states and explicit epsilon only for comparisons if needed.
// State swapping / rolling array: retain only the previous row when transitions need it.
// Recursion-to-iteration: process states in dependency order; replace recursion stack with a loop.
