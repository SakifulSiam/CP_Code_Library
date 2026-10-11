// WHEN: retain prefix versions and answer range kth queries. TIME: O(log n) per insert/query. ASSUMES: nonempty input; values are coordinate-compressed.
// Persistent frequency tree over compressed values; kth smallest in a subarray.
struct PersistentSegmentTree {
    struct Node { int left=0,right=0,sum=0; };
    vector<Node> t{{}}; vector<int> root; int n;
    PersistentSegmentTree(const vector<int>& a) {
        vector<int> v=a; sort(v.begin(),v.end()); v.erase(unique(v.begin(),v.end()),v.end()); n=v.size();
        root.push_back(0);
        for(int x:a) root.push_back(insert(root.back(),0,n-1,lower_bound(v.begin(),v.end(),x)-v.begin()));
        values=move(v);
    }
    vector<int> values;
    int insert(int old,int l,int r,int pos) {
        int cur=t.size(); t.push_back(t[old]); ++t[cur].sum;
        if(l<r) { int m=(l+r)/2; if(pos<=m)t[cur].left=insert(t[old].left,l,m,pos); else t[cur].right=insert(t[old].right,m+1,r,pos); }
        return cur;
    }
    int kthIndex(int leftRoot,int rightRoot,int k,int l,int r) const {
        if(l==r)return l;
        int leftCount=t[t[rightRoot].left].sum-t[t[leftRoot].left].sum,m=(l+r)/2;
        return k<=leftCount?kthIndex(t[leftRoot].left,t[rightRoot].left,k,l,m):kthIndex(t[leftRoot].right,t[rightRoot].right,k-leftCount,m+1,r);
    }
    int kth(int l,int r,int k) const { // inclusive zero-based [l,r]
        return values[kthIndex(root[l],root[r+1],k,0,n-1)];
    }
};
