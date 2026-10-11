// Point add and rectangle sum on a 1-indexed grid. TIME: O(log n log m).
struct Fenwick2D {
    int n, m;
    vector<vector<long long>> bit;
    Fenwick2D(int n, int m) : n(n), m(m), bit(n+1, vector<long long>(m+1)) {}
    void add(int x, int y, long long value) {
        for (int i=x; i<=n; i+=i&-i)
            for (int j=y; j<=m; j+=j&-j) bit[i][j] += value;
    }
    long long sumPrefix(int x, int y) const {
        long long ans=0;
        for (int i=x; i>0; i-=i&-i)
            for (int j=y; j>0; j-=j&-j) ans += bit[i][j];
        return ans;
    }
    long long rectangleSum(int x1,int y1,int x2,int y2) const {
        return sumPrefix(x2,y2)-sumPrefix(x1-1,y2)-sumPrefix(x2,y1-1)+sumPrefix(x1-1,y1-1);
    }
};
