// 0-indexed inclusive ranges; point assignment and range sum in O(log n).
struct SegmentTree {
    int n;
    vector<long long> tree;
    SegmentTree(const vector<long long>& a) : n((int)a.size()), tree(4 * max(1, (int)a.size())) { build(1, 0, n - 1, a); }
    void build(int p, int l, int r, const vector<long long>& a) {
        if (l == r) { tree[p] = a[l]; return; }
        int m = (l + r) / 2;
        build(p * 2, l, m, a); build(p * 2 + 1, m + 1, r, a);
        tree[p] = tree[p * 2] + tree[p * 2 + 1];
    }
    void setPoint(int i, long long value, int p, int l, int r) {
        if (l == r) { tree[p] = value; return; }
        int m = (l + r) / 2;
        if (i <= m) setPoint(i, value, p * 2, l, m); else setPoint(i, value, p * 2 + 1, m + 1, r);
        tree[p] = tree[p * 2] + tree[p * 2 + 1];
    }
    long long query(int ql, int qr, int p, int l, int r) const {
        if (qr < l || r < ql) return 0;
        if (ql <= l && r <= qr) return tree[p];
        int m = (l + r) / 2;
        return query(ql, qr, p * 2, l, m) + query(ql, qr, p * 2 + 1, m + 1, r);
    }
    void setPoint(int i, long long value) { setPoint(i, value, 1, 0, n - 1); }
    long long query(int l, int r) const { return query(l, r, 1, 0, n - 1); }
};
