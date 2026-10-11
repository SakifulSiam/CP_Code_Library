// 1-indexed; point add, prefix/range sum in O(log n).
template<class T>
struct Fenwick {
    int n;
    vector<T> bit;
    Fenwick(int n = 0) : n(n), bit(n + 1, T{}) {}
    void add(int i, T value) {
        for (; i <= n; i += i & -i) bit[i] += value;
    }
    T sumPrefix(int i) const {
        T ans{};
        for (; i > 0; i -= i & -i) ans += bit[i];
        return ans;
    }
    T sumRange(int l, int r) const { return sumPrefix(r) - sumPrefix(l - 1); }
};
