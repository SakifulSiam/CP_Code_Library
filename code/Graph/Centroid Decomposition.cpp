// WHEN: organize distance queries/updates by tree centroids. TIME: O(n log n) decomposition. ASSUMES: connected tree; callback handles each chosen centroid.
// Centroid decomposition skeleton; callback runs for each centroid before recursing.
struct CentroidDecomposition {
    int n; vector<vector<int>> g; vector<int> sub; vector<char> blocked;
    CentroidDecomposition(int n):n(n),g(n),sub(n),blocked(n){}
    void addEdge(int u,int v){g[u].push_back(v);g[v].push_back(u);}
    int calcSize(int v,int p){sub[v]=1;for(int u:g[v])if(u!=p&&!blocked[u])sub[v]+=calcSize(u,v);return sub[v];}
    int findCentroid(int v,int p,int total){for(int u:g[v])if(u!=p&&!blocked[u]&&sub[u]>total/2)return findCentroid(u,v,total);return v;}
    function<void(int)> processCentroid=[](int){};
    void build(int entry=0){int total=calcSize(entry,-1),c=findCentroid(entry,-1,total);processCentroid(c);blocked[c]=1;for(int u:g[c])if(!blocked[u])build(u);}
};
