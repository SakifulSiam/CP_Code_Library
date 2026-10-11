// WHEN: offline path queries with a toggleable vertex statistic. TIME: typically O((n+q)*sqrt(n)) toggles. ASSUMES: static tree; query conversion receives the LCA.
// Offline path queries using Mo's algorithm on the doubled Euler tour.
struct TreeMo {
    struct Query { int l,r,extra,id; };
    int n,timer=0; vector<vector<int>> g; vector<int> first,last,euler;
    TreeMo(int n):n(n),g(n),first(n),last(n){euler.reserve(2*n);}
    void addEdge(int u,int v){g[u].push_back(v);g[v].push_back(u);}
    void dfs(int v,int p){first[v]=euler.size();euler.push_back(v);for(int u:g[v])if(u!=p)dfs(u,v);last[v]=euler.size();euler.push_back(v);}
    void build(int root=0){dfs(root,-1);}
    Query makeQuery(int u,int v,int w,int id)const{
        if(first[u]>first[v])swap(u,v);
        if(w==u)return {first[u],first[v],-1,id};
        return {last[u],first[v],w,id};
    }
    template<class Toggle,class GetAnswer>
    vector<long long> solve(vector<Query> qs,Toggle toggle,GetAnswer getAnswer)const{
        int block=max(1,(int)sqrt(euler.size()));
        sort(qs.begin(),qs.end(),[&](auto a,auto b){int x=a.l/block,y=b.l/block;return x==y?((x&1)?a.r>b.r:a.r<b.r):x<y;});
        vector<long long> ans(qs.size()); vector<char> active(n); int L=0,R=-1;
        auto flip=[&](int pos){int v=euler[pos];active[v]=!active[v];toggle(v,active[v]);};
        for(auto q:qs){while(L>q.l)flip(--L);while(R<q.r)flip(++R);while(L<q.l)flip(L++);while(R>q.r)flip(R--);
            if(q.extra!=-1)toggle(q.extra,true);ans[q.id]=getAnswer();if(q.extra!=-1)toggle(q.extra,false);}
        return ans;
    }
};
