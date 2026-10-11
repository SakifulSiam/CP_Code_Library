// WHEN: answer per-subtree frequency/statistic queries. TIME: O(n log n) with small-to-large traversal. ASSUMES: caller supplies addVertex and saveAnswer callbacks.
// Sack/DSU-on-tree skeleton. Implement addVertex(v, delta) for the statistic you need.
struct DSUOnTree {
    int n; vector<vector<int>> g; vector<int> sub,heavy;
    function<void(int)> saveAnswer; // read the global statistic and store it for vertex v
    DSUOnTree(int n):n(n),g(n),sub(n),heavy(n,-1){}
    void addEdge(int u,int v){g[u].push_back(v);g[v].push_back(u);}
    function<void(int,int,int)> addVertex; // addVertex(v,+1) / removeVertex(v,-1)
    void calcSize(int v,int p){sub[v]=1;int best=0;for(int u:g[v])if(u!=p){calcSize(u,v);sub[v]+=sub[u];if(sub[u]>best)best=sub[u],heavy[v]=u;}}
    void addSubtree(int v,int p,int delta){addVertex(v,delta);for(int u:g[v])if(u!=p)addSubtree(u,v,delta);}
    void dfs(int v,int p,bool keep){
        for(int u:g[v])if(u!=p&&u!=heavy[v])dfs(u,v,false);
        if(heavy[v]!=-1)dfs(heavy[v],v,true);
        for(int u:g[v])if(u!=p&&u!=heavy[v])addSubtree(u,v,+1);
        addVertex(v,+1); if(saveAnswer)saveAnswer(v);
        if(!keep)addSubtree(v,p,-1);
    }
    void run(int root=0){calcSize(root,-1);dfs(root,-1,true);}
};
