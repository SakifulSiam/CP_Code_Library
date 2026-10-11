// Range sum with point updates, 0-indexed; O(sqrt(n)) per operation.
struct SqrtSum {
    int n, blockSize;
    vector<long long> a, block;
    SqrtSum(vector<long long> values) : n(values.size()), blockSize(max(1, (int)sqrt(n))), a(move(values)), block((n + blockSize - 1) / blockSize) {
        for (int i = 0; i < n; ++i) block[i / blockSize] += a[i];
    }
    void setValue(int i, long long value) { block[i / blockSize] += value - a[i]; a[i] = value; }
    long long query(int l, int r) const {
        long long ans = 0;
        while (l <= r && l % blockSize) ans += a[l++];
        while (l + blockSize - 1 <= r) { ans += block[l / blockSize]; l += blockSize; }
        while (l <= r) ans += a[l++];
        return ans;
    }
};
