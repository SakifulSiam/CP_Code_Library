// Range add and range sum; 0-indexed inclusive ranges.
struct LazySegmentTree {
    int n;
    vector<long long> tree, lazy;
    LazySegmentTree(int n) : n(n), tree(4 * n), lazy(4 * n) {}
    void apply(int p, int l, int r, long long value) {
        tree[p] += (r - l + 1LL) * value;
        lazy[p] += value;
    }
    void push(int p, int l, int r) {
        if (lazy[p] == 0 || l == r) return;
        int m = (l + r) / 2;
        apply(p * 2, l, m, lazy[p]); apply(p * 2 + 1, m + 1, r, lazy[p]);
        lazy[p] = 0;
    }
    void add(int ql, int qr, long long value, int p, int l, int r) {
        if (qr < l || r < ql) return;
        if (ql <= l && r <= qr) { apply(p, l, r, value); return; }
        push(p, l, r);
        int m = (l + r) / 2;
        add(ql, qr, value, p * 2, l, m); add(ql, qr, value, p * 2 + 1, m + 1, r);
        tree[p] = tree[p * 2] + tree[p * 2 + 1];
    }
    long long sum(int ql, int qr, int p, int l, int r) {
        if (qr < l || r < ql) return 0;
        if (ql <= l && r <= qr) return tree[p];
        push(p, l, r);
        int m = (l + r) / 2;
        return sum(ql, qr, p * 2, l, m) + sum(ql, qr, p * 2 + 1, m + 1, r);
    }
    void add(int l, int r, long long value) { add(l, r, value, 1, 0, n - 1); }
    long long sum(int l, int r) { return sum(l, r, 1, 0, n - 1); }
};
