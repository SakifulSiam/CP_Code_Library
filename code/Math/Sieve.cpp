// Sieve of Eratosthenes, Linear Sieve / SPF, and Segmented Sieve
#include <bits/stdc++.h>
using namespace std;

// Sieve with Smallest Prime Factor (SPF) for O(log n) prime factorization
vector<int> primes, spf;
void sieveSPF(int n) {
    spf.assign(n + 1, 0);
    for (int i = 2; i <= n; ++i) {
        if (!spf[i]) { spf[i] = i; primes.push_back(i); }
        for (int p : primes) {
            if (p > spf[i] || 1LL * i * p > n) break;
            spf[i * p] = p;
        }
    }
}
vector<int> getFactors(int x) {
    vector<int> f;
    while (x > 1) { f.push_back(spf[x]); x /= spf[x]; }
    return f;
}

// Segmented Sieve: primes in [L, R], where R - L <= 1e7, R <= 1e12
vector<long long> segmentedSieve(long long L, long long R) {
    long long lim = sqrt(R);
    vector<char> mark(lim + 1, 1);
    vector<long long> basePrimes;
    for (long long i = 2; i <= lim; ++i) {
        if (mark[i]) {
            basePrimes.push_back(i);
            for (long long j = i * i; j <= lim; j += i) mark[j] = 0;
        }
    }
    vector<char> isP(R - L + 1, 1);
    if (L == 1) isP[0] = 0;
    for (long long p : basePrimes) {
        for (long long j = max(p * p, (L + p - 1) / p * p); j <= R; j += p)
            isP[j - L] = 0;
    }
    vector<long long> res;
    for (long long i = 0; i <= R - L; ++i) if (isP[i]) res.push_back(L + i);
    return res;
}