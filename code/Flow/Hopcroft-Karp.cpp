// Maximum bipartite matching. Left vertices [0,n), right vertices [0,m).
// TIME: O(E sqrt(V)).
struct HopcroftKarp {
    int n, m;
    vector<vector<int>> g;
    vector<int> leftMatch, rightMatch, dist;
    int shortest;
    HopcroftKarp(int n, int m) : n(n), m(m), g(n), leftMatch(n,-1), rightMatch(m,-1), dist(n) {}
    void addEdge(int u, int v) { g[u].push_back(v); }
    bool bfs() {
        queue<int> q;
        for (int u=0; u<n; ++u) {
            if (leftMatch[u] == -1) dist[u]=0, q.push(u);
            else dist[u]=-1;
        }
        shortest=INT_MAX;
        while (!q.empty()) {
            int u=q.front(); q.pop();
            if (dist[u]+1>shortest) continue;
            for (int v:g[u]) {
                int w=rightMatch[v];
                if (w==-1) shortest=dist[u]+1;
                else if (dist[w]==-1) dist[w]=dist[u]+1, q.push(w);
            }
        }
        return shortest!=INT_MAX;
    }
    bool dfs(int u) {
        for (int v:g[u]) {
            int w=rightMatch[v];
            if ((w==-1 && dist[u]+1==shortest) ||
                (w!=-1 && dist[w]==dist[u]+1 && dfs(w))) {
                leftMatch[u]=v; rightMatch[v]=u; return true;
            }
        }
        dist[u]=-1; return false;
    }
    int maximumMatching() {
        int ans=0;
        while (bfs()) for (int u=0; u<n; ++u)
            if (leftMatch[u]==-1 && dfs(u)) ++ans;
        return ans;
    }
};
