// WHEN: DP needs range aggregates over compressed states. TIME: O(n log n) here. ASSUMES: strictly increasing subsequence; max-sum variant.
// Maximum-sum strictly increasing subsequence, using a segment tree over compressed values.
struct MaxSegTree {
    int n; vector<long long> t;
    MaxSegTree(int n):n(n),t(4*max(1,n),0){}
    void chmax(int i,long long x,int p,int l,int r) {
        if(l==r) { t[p]=max(t[p],x); return; }
        int m=(l+r)/2; if(i<=m) chmax(i,x,p*2,l,m); else chmax(i,x,p*2+1,m+1,r);
        t[p]=max(t[p*2],t[p*2+1]);
    }
    long long query(int ql,int qr,int p,int l,int r) const {
        if(qr<l||r<ql) return 0; if(ql<=l&&r<=qr) return t[p];
        int m=(l+r)/2; return max(query(ql,qr,p*2,l,m),query(ql,qr,p*2+1,m+1,r));
    }
    void chmax(int i,long long x) { chmax(i,x,1,0,n-1); }
    long long query(int l,int r) const { return l>r?0:query(l,r,1,0,n-1); }
};
long long maxIncreasingSubsequenceSumSeg(const vector<int>& a) {
    if(a.empty()) return 0;
    vector<int> v=a; sort(v.begin(),v.end()); v.erase(unique(v.begin(),v.end()),v.end());
    MaxSegTree st(v.size()); long long ans=LLONG_MIN;
    for(int x:a) { int i=lower_bound(v.begin(),v.end(),x)-v.begin(); long long cur=max((long long)x,st.query(0,i-1)+x); st.chmax(i,cur); ans=max(ans,cur); }
    return ans;
}
