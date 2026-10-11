// WHEN: compute subtree sizes and rerooted distance sums. TIME: O(n). ASSUMES: connected tree, 0-based vertices; recursive DFS may need an iterative rewrite for extreme depth.
// Tree DP: subtree sizes/sums, then reroot to get distance sum from every vertex.
// O(n), tree vertices 0..n-1; sumDist[u] = sum of distances from u to all vertices.
struct RerootTreeDP {
    int n; vector<vector<int>> g; vector<int> sub; vector<long long> down,sumDist;
    RerootTreeDP(int n):n(n),g(n),sub(n),down(n),sumDist(n){}
    void addEdge(int u,int v){g[u].push_back(v);g[v].push_back(u);}
    void dfs1(int v,int p){
        sub[v]=1; down[v]=0;
        for(int u:g[v])if(u!=p){dfs1(u,v);sub[v]+=sub[u];down[v]+=down[u]+sub[u];}
    }
    void dfs2(int v,int p){
        for(int u:g[v])if(u!=p){sumDist[u]=sumDist[v]+n-2LL*sub[u];dfs2(u,v);}
    }
    vector<long long> run(int root=0){
        dfs1(root,-1);sumDist[root]=down[root];dfs2(root,-1);return sumDist;
    }
};
