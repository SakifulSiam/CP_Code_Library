// State design: define what dp[...] means, transitions, base cases, and evaluation order.
// 0/1 knapsack: iterate capacity downward so each item is used at most once.
long long knapsack01(const vector<int>& w, const vector<long long>& val, int cap) {
    vector<long long> dp(cap + 1);
    for (int i = 0; i < (int)w.size(); ++i)
        for (int c = cap; c >= w[i]; --c) dp[c] = max(dp[c], dp[c-w[i]] + val[i]);
    return dp[cap];
}
// Unbounded coin change: iterate amount upward to allow repeated use.
long long minCoins(const vector<int>& coin, int amount) {
    const int INF = 1e9; vector<int> dp(amount+1, INF); dp[0]=0;
    for (int x=1;x<=amount;++x) for (int c:coin) if (c<=x) dp[x]=min(dp[x],dp[x-c]+1);
    return dp[amount] == INF ? -1 : dp[amount];
}
// Grid paths with obstacles: '#' blocked; reconstruct one shortest right/down path.
string gridPath(const vector<string>& g) {
    int n=g.size(), m=g[0].size(); vector<vector<int>> dp(n,vector<int>(m,1e9));
    if(g[0][0]=='#') return ""; dp[0][0]=0;
    for(int i=0;i<n;++i) for(int j=0;j<m;++j) if(g[i][j]!='#') {
        if(i) dp[i][j]=min(dp[i][j],dp[i-1][j]+1);
        if(j) dp[i][j]=min(dp[i][j],dp[i][j-1]+1);
    }
    if(dp[n-1][m-1]>=1e9) return "";
    string path; int i=n-1,j=m-1;
    while(i||j) { if(i && dp[i][j]==dp[i-1][j]+1) path+='D',--i; else path+='R',--j; }
    reverse(path.begin(),path.end()); return path;
}
// Real-valued DP: use double states and explicit epsilon only for comparisons if needed.
// State swapping / rolling array: retain only the previous row when transitions need it.
// Recursion-to-iteration: process states in dependency order; replace recursion stack with a loop.
