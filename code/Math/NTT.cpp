// Number Theoretic Transform (NTT) modulo 998244353. O(n log n) polynomial multiplication.
#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;
const int G = 3; // primitive root for 998244353

long long power(long long base, long long exp) {
    long long res = 1; base %= MOD;
    for (; exp > 0; exp >>= 1, base = base * base % MOD) if (exp & 1) res = res * base % MOD;
    return res;
}
long long modInverse(long long n) { return power(n, MOD - 2); }

void ntt(vector<int>& a, bool invert) {
    int n = a.size();
    for (int i = 1, j = 0; i < n; ++i) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) swap(a[i], a[j]);
    }
    for (int len = 2; len <= n; len <<= 1) {
        long long wlen = power(G, (MOD - 1) / len);
        if (invert) wlen = modInverse(wlen);
        for (int i = 0; i < n; i += len) {
            long long w = 1;
            for (int j = 0; j < len / 2; ++j) {
                long long u = a[i + j];
                long long v = a[i + j + len / 2] * w % MOD;
                a[i + j] = (u + v) % MOD;
                a[i + j + len / 2] = (u - v + MOD) % MOD;
                w = w * wlen % MOD;
            }
        }
    }
    if (invert) {
        long long n_inv = modInverse(n);
        for (int& x : a) x = x * n_inv % MOD;
    }
}

vector<int> multiply(vector<int> a, vector<int> b) {
    int n = 1;
    int target = a.size() + b.size() - 1;
    while (n < target) n <<= 1;
    a.resize(n); b.resize(n);
    ntt(a, false); ntt(b, false);
    for (int i = 0; i < n; ++i) a[i] = 1LL * a[i] * b[i] % MOD;
    ntt(a, true);
    a.resize(target);
    return a;
}
