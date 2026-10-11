// WHEN: sparse range add/sum over a huge domain. TIME: O(log C) per operation. ASSUMES: coordinates in [0,1e9]; sums fit long long.
// Dynamic range add / range sum on a large fixed domain [0, LIMIT].
struct DynamicSegmentTree {
    static const int LIMIT=1000000000;
    struct Node { long long sum=0,lazy=0; int left=-1,right=-1; };
    vector<Node> t{Node()};
    int makeNode(){t.push_back(Node());return (int)t.size()-1;}
    void apply(int p,int l,int r,long long x){t[p].sum+=(r-l+1LL)*x;t[p].lazy+=x;}
    void push(int p,int l,int r){
        if(l==r||t[p].lazy==0)return;
        int m=l+(r-l)/2;
        if(t[p].left==-1)t[p].left=makeNode(); if(t[p].right==-1)t[p].right=makeNode();
        int a=t[p].left,b=t[p].right; long long z=t[p].lazy; t[p].lazy=0;
        apply(a,l,m,z); apply(b,m+1,r,z);
    }
    void add(int ql,int qr,long long x,int p,int l,int r){
        if(qr<l||r<ql)return; if(ql<=l&&r<=qr){apply(p,l,r,x);return;}
        push(p,l,r); int m=l+(r-l)/2;
        if(t[p].left==-1)t[p].left=makeNode(); if(t[p].right==-1)t[p].right=makeNode();
        int a=t[p].left,b=t[p].right; add(ql,qr,x,a,l,m); add(ql,qr,x,b,m+1,r); t[p].sum=t[a].sum+t[b].sum;
    }
    long long sum(int ql,int qr,int p,int l,int r){
        if(qr<l||r<ql)return 0; if(ql<=l&&r<=qr)return t[p].sum;
        if(t[p].left==-1&&t[p].right==-1)return t[p].lazy*(min(r,qr)-max(l,ql)+1LL);
        push(p,l,r); int m=l+(r-l)/2; long long ans=0;
        if(t[p].left!=-1)ans+=sum(ql,qr,t[p].left,l,m);
        if(t[p].right!=-1)ans+=sum(ql,qr,t[p].right,m+1,r);
        return ans;
    }
    void add(int l,int r,long long x){add(l,r,x,0,0,LIMIT);}
    long long sum(int l,int r){return sum(l,r,0,0,LIMIT);}
};
