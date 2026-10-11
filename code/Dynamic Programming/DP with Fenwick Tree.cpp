// WHEN: DP needs prefix aggregates after coordinate compression. TIME: O(n log n) here. ASSUMES: strictly increasing subsequence; max-sum variant.
// Maximum-sum strictly increasing subsequence; coordinate compression + Fenwick max.
struct FenwickMax {
    int n; vector<long long> bit;
    FenwickMax(int n):n(n),bit(n+1,0){}
    void update(int i,long long x) { for(;i<=n;i+=i&-i) bit[i]=max(bit[i],x); }
    long long query(int i) const { long long ans=0; for(;i;i-=i&-i) ans=max(ans,bit[i]); return ans; }
};
long long maxIncreasingSubsequenceSum(const vector<int>& a) {
    if(a.empty()) return 0;
    vector<int> vals=a; sort(vals.begin(),vals.end()); vals.erase(unique(vals.begin(),vals.end()),vals.end());
    FenwickMax fw(vals.size()); long long answer=LLONG_MIN;
    for(int x:a) { int r=lower_bound(vals.begin(),vals.end(),x)-vals.begin()+1;
        long long cur=max((long long)x,fw.query(r-1)+x); fw.update(r,cur); answer=max(answer,cur); }
    return answer;
}
