// Gaussian Elimination: real (double) and modular (mod prime p) linear equation solvers.
#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-9;
const int INF = 2; // 0: no solution, 1: unique solution, INF: infinitely many

// 1. Double precision solver: a is n x (m + 1) augmented matrix; ans contains solution
int gaussDouble(vector<vector<double>> a, vector<double>& ans) {
    int n = a.size(), m = a[0].size() - 1;
    vector<int> where(m, -1);
    for (int col = 0, row = 0; col < m && row < n; ++col) {
        int sel = row;
        for (int i = row; i < n; ++i)
            if (abs(a[i][col]) > abs(a[sel][col])) sel = i;
        if (abs(a[sel][col]) < EPS) continue;
        swap(a[sel], a[row]);
        where[col] = row;
        for (int i = 0; i < n; ++i) if (i != row) {
            double c = a[i][col] / a[row][col];
            for (int j = col; j <= m; ++j) a[i][j] -= a[row][j] * c;
        }
        ++row;
    }
    ans.assign(m, 0);
    for (int i = 0; i < m; ++i)
        if (where[i] != -1) ans[i] = a[where[i]][m] / a[where[i]][i];
    for (int i = 0; i < n; ++i) {
        double sum = 0;
        for (int j = 0; j < m; ++j) sum += ans[j] * a[i][j];
        if (abs(sum - a[i][m]) > EPS) return 0;
    }
    for (int i = 0; i < m; ++i) if (where[i] == -1) return INF;
    return 1;
}

// 2. Modulo Prime p solver: powerMod and modInverse helper
long long modPow(long long a, long long b, long long mod) {
    long long res = 1; a %= mod;
    for (; b; b >>= 1, a = a * a % mod) if (b & 1) res = res * a % mod;
    return res;
}

int gaussMod(vector<vector<int>> a, vector<int>& ans, int mod) {
    int n = a.size(), m = a[0].size() - 1;
    vector<int> where(m, -1);
    for (int col = 0, row = 0; col < m && row < n; ++col) {
        int sel = row;
        for (int i = row; i < n; ++i) if (a[i][col] > 0) { sel = i; break; }
        if (a[sel][col] == 0) continue;
        swap(a[sel], a[row]);
        where[col] = row;
        int inv = modPow(a[row][col], mod - 2, mod);
        for (int j = col; j <= m; ++j) a[row][j] = 1LL * a[row][j] * inv % mod;
        for (int i = 0; i < n; ++i) if (i != row && a[i][col]) {
            int c = a[i][col];
            for (int j = col; j <= m; ++j)
                a[i][j] = (a[i][j] - 1LL * a[row][j] * c % mod + mod) % mod;
        }
        ++row;
    }
    ans.assign(m, 0);
    for (int i = 0; i < m; ++i) if (where[i] != -1) ans[i] = a[where[i]][m];
    for (int i = 0; i < n; ++i) {
        int sum = 0;
        for (int j = 0; j < m; ++j) sum = (sum + 1LL * ans[j] * a[i][j]) % mod;
        if (sum != a[i][m]) return 0;
    }
    for (int i = 0; i < m; ++i) if (where[i] == -1) return INF;
    return 1;
}
