// WHEN: foundational graph traversals/shortest paths/MST. TIME: BFS/DFS/toposort O(V+E), Dijkstra O((V+E)logV), Kruskal O(E log E). ASSUMES: Dijkstra weights nonnegative; 0-1 BFS weights only 0/1.
// Unweighted graph: BFS distances and parents in O(V+E).
vector<int> bfsDistances(const vector<vector<int>>& g, int source) {
    vector<int> dist(g.size(), -1), parent(g.size(), -1);
    queue<int> q; dist[source]=0; q.push(source);
    while(!q.empty()) {
        int v=q.front(); q.pop();
        for(int u:g[v]) if(dist[u]==-1) {
            dist[u]=dist[v]+1; parent[u]=v; q.push(u);
        }
    }
    return dist;
}
// Multi-source BFS: push all source nodes into queue with dist[s]=0 initially, then run standard BFS.
// Finds shortest unweighted distance to the nearest source in O(V+E).

// Iterative DFS order; avoids recursion depth issues on large graphs.
vector<int> dfsOrder(const vector<vector<int>>& g,int source) {
    vector<char> seen(g.size()); vector<int> order, st{source}; seen[source]=1;
    while(!st.empty()) {
        int v=st.back(); st.pop_back(); order.push_back(v);
        for(int u:g[v]) if(!seen[u]) seen[u]=1,st.push_back(u);
    }
    return order;
}

// Dijkstra: nonnegative edge weights, O((V+E) log V).
vector<long long> dijkstra(const vector<vector<pair<int,int>>>& g,int source) {
    const long long INF=(1LL<<62);
    vector<long long> dist(g.size(),INF); priority_queue<pair<long long,int>,vector<pair<long long,int>>,greater<pair<long long,int>>> pq;
    dist[source]=0; pq.push({0,source});
    while(!pq.empty()) {
        auto [d,v]=pq.top(); pq.pop(); if(d!=dist[v]) continue;
        for(auto [u,w]:g[v]) if(dist[u]>d+w) dist[u]=d+w,pq.push({dist[u],u});
    }
    return dist;
}

// 0-1 BFS: every edge weight must be 0 or 1; O(V+E).
vector<int> zeroOneBFS(const vector<vector<pair<int,int>>>& g,int source) {
    const int INF=1e9; vector<int> dist(g.size(),INF); deque<int> dq;
    dist[source]=0; dq.push_front(source);
    while(!dq.empty()) {
        int v=dq.front(); dq.pop_front();
        for(auto [u,w]:g[v]) if(dist[u]>dist[v]+w) {
            dist[u]=dist[v]+w; if(w==0)dq.push_front(u);else dq.push_back(u);
        }
    }
    return dist;
}

// Topological order by Kahn's algorithm; empty result means a directed cycle.
vector<int> topologicalSort(const vector<vector<int>>& g) {
    vector<int> indeg(g.size()),order;
    for(auto& edges:g) for(int u:edges) ++indeg[u];
    queue<int> q; for(int v=0;v<(int)g.size();++v)if(!indeg[v])q.push(v);
    while(!q.empty()) { int v=q.front();q.pop();order.push_back(v);for(int u:g[v])if(--indeg[u]==0)q.push(u); }
    if(order.size()!=g.size())return {}; return order;
}

// Kruskal MST for an undirected graph. DSU is local to keep this snippet standalone.
struct MSTEdge { int u,v; long long w; };
pair<bool,long long> kruskalMST(int n,vector<MSTEdge> edges) {
    sort(edges.begin(),edges.end(),[](auto a,auto b){return a.w<b.w;});
    vector<int> p(n),sz(n,1); iota(p.begin(),p.end(),0);
    function<int(int)> find=[&](int v){return p[v]==v?v:p[v]=find(p[v]);};
    long long total=0; int used=0;
    for(auto e:edges) { int a=find(e.u),b=find(e.v);if(a==b)continue;
        if(sz[a]<sz[b])swap(a,b);p[b]=a;sz[a]+=sz[b];total+=e.w;++used; }
    return {used==n-1,total}; // false for disconnected graph (except n=1)
}
