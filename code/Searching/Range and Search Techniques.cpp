// 2D prefix sum: build then sum inclusive rectangle (x1,y1)..(x2,y2).
vector<vector<long long>> prefix2D(const vector<vector<int>>& a) {
    int n = a.size(), m = n ? a[0].size() : 0;
    vector<vector<long long>> p(n + 1, vector<long long>(m + 1));
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j)
        p[i][j] = a[i-1][j-1] + p[i-1][j] + p[i][j-1] - p[i-1][j-1];
    return p;
}
long long rectangleSum(const vector<vector<long long>>& p, int x1, int y1, int x2, int y2) {
    return p[x2+1][y2+1] - p[x1][y2+1] - p[x2+1][y1] + p[x1][y1];
}

// Ternary search for a unimodal function on a closed interval.
double ternarySearch(double l, double r, function<double(double)> f) {
    for (int it = 0; it < 100; ++it) {
        double m1 = l + (r-l)/3, m2 = r - (r-l)/3;
        if (f(m1) < f(m2)) l = m1; else r = m2; // maximum; reverse for minimum
    }
    return (l+r)/2;
}

// Meet in the middle: all subset sums, O(2^(n/2)) time and memory per half.
vector<long long> subsetSums(const vector<long long>& a, int l, int r) {
    vector<long long> sums{0};
    for (int i = l; i < r; ++i) {
        int old = sums.size();
        for (int j = 0; j < old; ++j) sums.push_back(sums[j] + a[i]);
    }
    return sums;
}
// 4-sum existence with four distinct indices, expected O(n^2) time and memory.
bool fourSum(const vector<long long>& a, long long target) {
    unordered_set<long long> earlierPairSums;
    int n=a.size();
    for (int i=0;i<n;++i) {
        for (int j=i+1;j<n;++j)
            if (earlierPairSums.count(target-a[i]-a[j])) return true;
        for (int x=0;x<i;++x) earlierPairSums.insert(a[x]+a[i]);
    }
    return false;
}
