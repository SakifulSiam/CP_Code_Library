// WHEN: interval DP satisfies Knuth monotonicity. TIME: O(n^2). ASSUMES: prove the quadrangle inequality/monotone-opt property for the recurrence.
// Interval DP optimization. Requires a valid quadrangle/monotone-opt condition.
// Replace cost(l,r) with the problem's interval cost; indices are inclusive.
template<class Cost>
vector<vector<long long>> knuthDP(int n,Cost cost) {
    const long long INF=(1LL<<62);
    vector<vector<long long>> dp(n,vector<long long>(n));
    vector<vector<int>> opt(n,vector<int>(n));
    for(int i=0;i<n;++i)opt[i][i]=i;
    for(int len=2;len<=n;++len) for(int l=0;l+len<=n;++l) {
        int r=l+len-1; dp[l][r]=INF;
        int from=max(l,opt[l][r-1]),to=min(r-1,opt[l+1][r]);
        for(int k=from;k<=to;++k) {
            long long cur=(k>=l?dp[l][k]:0)+(k+1<=r?dp[k+1][r]:0)+cost(l,r);
            if(cur<dp[l][r])dp[l][r]=cur,opt[l][r]=k;
        }
    }
    return dp;
}
