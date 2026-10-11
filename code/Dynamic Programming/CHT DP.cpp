// WHEN: DP transitions are line queries with ordered slopes and x values. TIME: O(1) amortized per operation. ASSUMES: slopes decrease and query x increases.
// Monotone convex hull trick for maximum of m*x+b: slopes decreasing, x queries increasing.
struct MonotoneCHT {
    struct Line { long long m,b; long long at(long long x) const { return m*x+b; } };
    deque<Line> hull;
    bool redundant(Line a,Line b,Line c) {
        return (__int128)(b.b-a.b)*(b.m-c.m)>=(__int128)(c.b-b.b)*(a.m-b.m);
    }
    void add(long long m,long long b) {
        Line x{m,b}; if(!hull.empty()&&hull.back().m==m) {
            if(hull.back().b>=b)return; hull.pop_back();
        }
        while(hull.size()>=2&&redundant(hull[hull.size()-2],hull.back(),x))hull.pop_back();
        hull.push_back(x);
    }
    long long query(long long x) {
        while(hull.size()>=2&&hull[0].at(x)<=hull[1].at(x))hull.pop_front();
        return hull.front().at(x);
    }
};
// Example recurrence: dp[i] = max_j(m[j]*x[i]+b[j]); add each candidate line, then query x[i].
