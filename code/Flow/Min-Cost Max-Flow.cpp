// Successive shortest augmenting paths with SPFA. TIME: O(F*V*E).
// Supports negative edge costs; assumes no reachable negative-cost cycle.
struct MinCostMaxFlow {
    struct Edge { int to, rev, cap; long long cost; };
    int n;
    vector<vector<Edge>> g;
    MinCostMaxFlow(int n) : n(n), g(n) {}
    void addEdge(int u,int v,int cap,long long cost) {
        Edge a{v,(int)g[v].size(),cap,cost}, b{u,(int)g[u].size(),0,-cost};
        g[u].push_back(a); g[v].push_back(b);
    }
    pair<int,long long> run(int s,int t) {
        int flow=0; long long cost=0;
        const long long INF=(1LL<<60);
        while (true) {
            vector<long long> d(n,INF); vector<int> pv(n,-1), pe(n,-1);
            vector<char> inQ(n); queue<int> q; d[s]=0; q.push(s); inQ[s]=1;
            while (!q.empty()) {
                int v=q.front(); q.pop(); inQ[v]=0;
                for (int i=0;i<(int)g[v].size();++i) {
                    auto &e=g[v][i];
                    if (e.cap && d[e.to]>d[v]+e.cost) {
                        d[e.to]=d[v]+e.cost; pv[e.to]=v; pe[e.to]=i;
                        if (!inQ[e.to]) q.push(e.to), inQ[e.to]=1;
                    }
                }
            }
            if (d[t]==INF) break;
            int add=INT_MAX;
            for (int v=t;v!=s;v=pv[v]) add=min(add,g[pv[v]][pe[v]].cap);
            for (int v=t;v!=s;v=pv[v]) {
                Edge &e=g[pv[v]][pe[v]]; e.cap-=add; g[v][e.rev].cap+=add;
            }
            flow+=add; cost+=1LL*add*d[t];
        }
        return {flow,cost};
    }
};
