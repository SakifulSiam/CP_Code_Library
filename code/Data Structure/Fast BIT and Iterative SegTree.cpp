// 1. Iterative Segment Tree (point update, range query on [l, r) in O(log n))
#include <bits/stdc++.h>
using namespace std;

template<typename T>
struct IterativeSegTree {
    int n; vector<T> tree;
    IterativeSegTree(int n) : n(n), tree(2 * n, 0) {}
    void update(int p, T val) {
        for (tree[p += n] = val; p > 1; p >>= 1) tree[p >> 1] = tree[p] + tree[p ^ 1];
    }
    T query(int l, int r) { // range [l, r)
        T res = 0;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) res += tree[l++];
            if (r & 1) res += tree[--r];
        }
        return res;
    }
};

// 2. Fenwick Tree with Range Update and Range Query (1-indexed)
struct RangeFenwick {
    int n; vector<long long> b1, b2;
    RangeFenwick(int n) : n(n), b1(n + 1, 0), b2(n + 1, 0) {}
    void add(vector<long long>& b, int idx, long long val) {
        for (; idx <= n; idx += idx & -idx) b[idx] += val;
    }
    void rangeUpdate(int l, int r, long long val) {
        add(b1, l, val); add(b1, r + 1, -val);
        add(b2, l, val * (l - 1)); add(b2, r + 1, -val * r);
    }
    long long prefixSum(int idx) {
        long long sum1 = 0, sum2 = 0;
        for (int i = idx; i > 0; i -= i & -i) { sum1 += b1[i]; sum2 += b2[i]; }
        return sum1 * idx - sum2;
    }
    long long rangeQuery(int l, int r) { return prefixSum(r) - prefixSum(l - 1); }
};

// 3. BIT Descent: find smallest index with prefix sum >= k in O(log n) (1-indexed frequencies >= 0)
struct BITDescent {
    int n; vector<int> tree;
    BITDescent(int n) : n(n), tree(n + 1, 0) {}
    void add(int idx, int val) { for (; idx <= n; idx += idx & -idx) tree[idx] += val; }
    int findKth(int k) { // returns 1-based index
        int idx = 0;
        for (int p = 1 << __lg(n); p > 0; p >>= 1) {
            if (idx + p <= n && tree[idx + p] < k) {
                idx += p;
                k -= tree[idx];
            }
        }
        return idx + 1;
    }
};
