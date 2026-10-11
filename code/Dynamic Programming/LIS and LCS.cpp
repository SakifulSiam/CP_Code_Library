// LIS length in O(n log n), strictly increasing.
int lisLength(const vector<int>& a) {
    vector<int> tails;
    for (int x : a) { auto it=lower_bound(tails.begin(),tails.end(),x); if(it==tails.end()) tails.push_back(x); else *it=x; }
    return tails.size();
}
// LCS length in O(n*m); can reduce memory by swapping to keep the shorter string in columns.
int lcsLength(const string& a, const string& b) {
    vector<int> dp(b.size()+1);
    for(char x:a) { int diagonal=0; for(int j=1;j<=(int)b.size();++j) {
        int old=dp[j]; dp[j]=(x==b[j-1]?diagonal+1:max(dp[j],dp[j-1])); diagonal=old;
    }}
    return dp.back();
}
