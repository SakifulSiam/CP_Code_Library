// Dinic's Algorithm for Maximum Flow. Complexity: O(V^2 E), for unit networks O(E sqrt(V)).
// Nodes 0-indexed. Capacities and flow use long long.
using ll = long long;
struct Dinic {
    struct Edge {
        int u, v;
        ll cap, flow = 0;
        Edge(int u, int v, ll cap) : u(u), v(v), cap(cap) {}
    };
    int N;
    vector<Edge> edge;
    vector<vector<int>> adj;
    vector<int> d, pt;
    Dinic(int N) : N(N), adj(N), d(N), pt(N) {}
    void addEdge(int u, int v, ll cap) {
        if (u == v) return;
        edge.emplace_back(u, v, cap);
        adj[u].push_back(edge.size() - 1);
        edge.emplace_back(v, u, 0);
        adj[v].push_back(edge.size() - 1);
    }
    bool bfs(int s, int t) {
        queue<int> q({ s });
        fill(d.begin(), d.end(), N + 1);
        d[s] = 0;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            if (u == t) break;
            for (int k : adj[u]) {
                Edge& e = edge[k];
                if (e.flow < e.cap && d[e.v] > d[u] + 1) {
                    d[e.v] = d[u] + 1;
                    q.push(e.v);
                }
            }
        }
        return d[t] != N + 1;
    }
    ll dfs(int u, int T, ll flow = -1) {
        if (u == T || flow == 0) return flow;
        for (int& i = pt[u]; i < (int)adj[u].size(); i++) {
            Edge& e = edge[adj[u][i]];
            Edge& oe = edge[adj[u][i] ^ 1];
            if (d[e.v] == d[u] + 1) {
                ll amt = e.cap - e.flow;
                if (flow != -1 && amt > flow) amt = flow;
                if (ll pushed = dfs(e.v, T, amt)) {
                    e.flow += pushed;
                    oe.flow -= pushed;
                    return pushed;
                }
            }
        }
        return 0;
    }
    ll maxFlow(int s, int t) {
        ll total = 0;
        while (bfs(s, t)) {
            fill(pt.begin(), pt.end(), 0);
            while (ll flow = dfs(s, t)) total += flow;
        }
        return total;
    }
};
