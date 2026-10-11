// WHEN: undo unions in offline dynamic connectivity. TIME: find/unite O(log n), rollback O(changes). ASSUMES: no path compression; snapshot is history size.
// No path compression: union by size keeps tree height O(log n), enabling rollback.
struct RollbackDSU {
    vector<int> parent,size;
    vector<pair<int,int>> history; // {child root, old size of receiving root}; {-1,-1} = no-op
    int components;
    RollbackDSU(int n):parent(n),size(n,1),components(n){iota(parent.begin(),parent.end(),0);}
    int find(int v) const { while(v!=parent[v]) v=parent[v]; return v; }
    int snapshot() const { return history.size(); }
    bool unite(int a,int b) {
        a=find(a); b=find(b);
        if(a==b) { history.push_back({-1,-1}); return false; }
        if(size[a]<size[b]) swap(a,b);
        history.push_back({b,size[a]}); parent[b]=a; size[a]+=size[b]; --components; return true;
    }
    void rollback(int snap) {
        while((int)history.size()>snap) {
            auto [b,oldSize]=history.back(); history.pop_back();
            if(b==-1) continue;
            int a=parent[b]; parent[b]=b; size[a]=oldSize; ++components;
        }
    }
};
