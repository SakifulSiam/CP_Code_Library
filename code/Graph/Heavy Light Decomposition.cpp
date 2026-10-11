// WHEN: path queries/updates on a static tree. TIME: O(log^2 n) path query. ASSUMES: 0-based connected tree; this template supports point assignment and path sum.
// HLD for point assignment and path sum; vertices are 0-indexed.
struct HLD {
    int n,timer=0; vector<vector<int>> g; vector<int> parent,depth,heavy,head,pos,sub;
    vector<long long> base,seg;
    HLD(int n):n(n),g(n),parent(n,-1),depth(n),heavy(n,-1),head(n),pos(n),sub(n),base(n),seg(4*n){}
    void addEdge(int u,int v){g[u].push_back(v);g[v].push_back(u);}
    int dfsSize(int v,int p){parent[v]=p;sub[v]=1;int best=0;
        for(int u:g[v])if(u!=p){depth[u]=depth[v]+1;int z=dfsSize(u,v);sub[v]+=z;if(z>best)best=z,heavy[v]=u;}return sub[v];}
    void decompose(int v,int h){head[v]=h;pos[v]=timer++;
        if(heavy[v]!=-1)decompose(heavy[v],h);
        for(int u:g[v])if(u!=parent[v]&&u!=heavy[v])decompose(u,u);}
    void build(int root=0){dfsSize(root,-1);decompose(root,root);}
    void segSet(int i,long long x,int p,int l,int r){if(l==r){seg[p]=x;return;}int m=(l+r)/2;if(i<=m)segSet(i,x,p*2,l,m);else segSet(i,x,p*2+1,m+1,r);seg[p]=seg[p*2]+seg[p*2+1];}
    long long segSum(int ql,int qr,int p,int l,int r)const{if(qr<l||r<ql)return 0;if(ql<=l&&r<=qr)return seg[p];int m=(l+r)/2;return segSum(ql,qr,p*2,l,m)+segSum(ql,qr,p*2+1,m+1,r);}
    void setValue(int v,long long x){segSet(pos[v],x,1,0,n-1);}
    long long pathSum(int a,int b)const{long long ans=0;while(head[a]!=head[b]){if(depth[head[a]]<depth[head[b]])swap(a,b);ans+=segSum(pos[head[a]],pos[a],1,0,n-1);a=parent[head[a]];}if(depth[a]>depth[b])swap(a,b);return ans+segSum(pos[a],pos[b],1,0,n-1);}
};
