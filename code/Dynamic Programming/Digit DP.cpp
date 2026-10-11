// Count integers in [0, bound] whose digit sum is divisible by k.
long long countDigitSumDivisible(const string& bound,int k) {
    int n=bound.size();
    vector<vector<array<long long,2>>> memo(n+1,vector<array<long long,2>>(k));
    vector<vector<array<char,2>>> seen(n+1,vector<array<char,2>>(k));
    function<long long(int,int,int)> dfs=[&](int pos,int rem,int tight)->long long {
        if(pos==n) return rem==0;
        if(seen[pos][rem][tight]) return memo[pos][rem][tight];
        seen[pos][rem][tight]=1;
        int lim=tight?bound[pos]-'0':9; long long ans=0;
        for(int d=0;d<=lim;++d) ans+=dfs(pos+1,(rem+d)%k,tight&&(d==lim));
        return memo[pos][rem][tight]=ans;
    };
    return dfs(0,0,1);
}
