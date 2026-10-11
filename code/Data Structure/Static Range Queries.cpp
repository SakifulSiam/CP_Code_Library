// Sparse table: immutable array, O(1) idempotent queries (min/max/gcd).
struct SparseTable {
    vector<vector<int>> st;
    vector<int> lg;
    SparseTable(const vector<int>& a) {
        int n = a.size(); lg.resize(n + 1);
        for (int i = 2; i <= n; ++i) lg[i] = lg[i/2] + 1;
        st.assign(lg[n] + 1, vector<int>(n)); st[0] = a;
        for (int k = 1; k < (int)st.size(); ++k)
            for (int i = 0; i + (1 << k) <= n; ++i)
                st[k][i] = min(st[k-1][i], st[k-1][i + (1 << (k-1))]);
    }
    int queryMin(int l, int r) const {
        int k = lg[r-l+1]; return min(st[k][l], st[k][r-(1<<k)+1]);
    }
};

// Merge sort tree: static range count of values <= x, O(log^2 n) per query.
struct MergeSortTree {
    int n; vector<vector<int>> t;
    MergeSortTree(const vector<int>& a) : n(a.size()), t(4 * max(1, (int)a.size())) { build(1,0,n-1,a); }
    void build(int p,int l,int r,const vector<int>& a) {
        if (l==r) { t[p]={a[l]}; return; }
        int m=(l+r)/2; build(p*2,l,m,a); build(p*2+1,m+1,r,a);
        merge(t[p*2].begin(),t[p*2].end(),t[p*2+1].begin(),t[p*2+1].end(),back_inserter(t[p]));
    }
    int countLE(int ql,int qr,int x,int p,int l,int r) const {
        if (qr<l || r<ql) return 0;
        if (ql<=l && r<=qr) return upper_bound(t[p].begin(),t[p].end(),x)-t[p].begin();
        int m=(l+r)/2; return countLE(ql,qr,x,p*2,l,m)+countLE(ql,qr,x,p*2+1,m+1,r);
    }
    int countLE(int l,int r,int x) const { return countLE(l,r,x,1,0,n-1); }
};
