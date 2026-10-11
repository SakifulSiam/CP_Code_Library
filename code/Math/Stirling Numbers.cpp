// Stirling numbers of the second kind S(n,k) modulo MOD.
vector<vector<long long>> stirlingSecondKind(int n,int k,long long MOD) {
    vector<vector<long long>> s(n+1,vector<long long>(k+1)); s[0][0]=1;
    for(int i=1;i<=n;++i) for(int j=1;j<=min(i,k);++j)
        s[i][j]=(j*s[i-1][j]+s[i-1][j-1])%MOD;
    return s;
}
