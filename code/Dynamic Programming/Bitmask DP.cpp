// Assignment-style bitmask DP: n <= about 20. dp[mask] = best cost after choosing mask.
long long assignmentDP(const vector<vector<int>>& cost) {
    int n=cost.size(), N=1<<n; const long long INF=(1LL<<60);
    vector<long long> dp(N,INF); dp[0]=0;
    for(int mask=0;mask<N;++mask) {
        int row=__builtin_popcount((unsigned)mask);
        if(row==n || dp[mask]==INF) continue;
        for(int col=0;col<n;++col) if(!(mask>>col&1)) {
            int next=mask|(1<<col); dp[next]=min(dp[next],dp[mask]+cost[row][col]);
        }
    }
    return dp[N-1];
}

