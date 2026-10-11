// WHEN: arbitrary line insertions and minimum queries. TIME: O(log C) per operation. ASSUMES: integer x in [-1e9,1e9]; products fit long long.
// Li Chao tree for minimum line queries on a fixed integer x-domain.
struct DynamicLiChao {
    static const int XMIN=-1000000000, XMAX=1000000000;
    struct Line { long long m=0,b=(1LL<<62); long long eval(int x) const { return m*x+b; } };
    struct Node { Line line; int left=-1,right=-1; };
    vector<Node> t{Node()};
    int makeNode(){t.push_back(Node());return (int)t.size()-1;}
    void add(Line nw,int p,int l,int r) {
        int m=l+(r-l)/2; bool lef=nw.eval(l)<t[p].line.eval(l),mid=nw.eval(m)<t[p].line.eval(m);
        if(mid)swap(nw,t[p].line); if(l==r)return;
        if(lef!=mid) { if(t[p].left==-1)t[p].left=makeNode(); int c=t[p].left; add(nw,c,l,m); }
        else { if(t[p].right==-1)t[p].right=makeNode(); int c=t[p].right; add(nw,c,m+1,r); }
    }
    long long query(int x,int p,int l,int r) const {
        long long ans=t[p].line.eval(x); if(l==r)return ans; int m=l+(r-l)/2;
        int c=x<=m?t[p].left:t[p].right;
        if(c==-1)return ans;
        return min(ans,query(x,c,x<=m?l:m+1,x<=m?m:r));
    }
    void addLine(long long m,long long b){add({m,b},0,XMIN,XMAX);}
    long long query(int x) const {return query(x,0,XMIN,XMAX);}
};
