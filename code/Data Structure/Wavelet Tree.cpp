// WHEN: static range kth queries. TIME: O(log sigma) per query. ASSUMES: values fit the constructor domain; array does not change.
// Static range kth-smallest. Build on values in [lo,hi]; query uses inclusive zero-based indices.
struct WaveletTree {
    int lo,hi; vector<int> leftCount; unique_ptr<WaveletTree> left,right;
    WaveletTree(const vector<int>& a,int x,int y):lo(x),hi(y) {
        leftCount.assign(a.size()+1,0); if(a.empty()||lo==hi)return;
        int mid=lo+(hi-lo)/2; vector<int> l,r; l.reserve(a.size()); r.reserve(a.size());
        for(int i=0;i<(int)a.size();++i) {
            bool goLeft=a[i]<=mid; leftCount[i+1]=leftCount[i]+goLeft;
            (goLeft?l:r).push_back(a[i]);
        }
        if(!l.empty())left=make_unique<WaveletTree>(l,lo,mid);
        if(!r.empty())right=make_unique<WaveletTree>(r,mid+1,hi);
    }
    int kth(int l,int r,int k) const { // k is 1-indexed
        if(lo==hi)return lo;
        int inLeft=leftCount[r+1]-leftCount[l];
        if(k<=inLeft)return left->kth(leftCount[l],leftCount[r+1]-1,k);
        return right->kth(l-leftCount[l],r-leftCount[r+1],k-inLeft);
    }
};
