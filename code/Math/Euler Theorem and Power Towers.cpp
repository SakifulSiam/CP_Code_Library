// Power Tower modulo m using generalized Euler's reduction theorem:
// a^b mod m = a^(b < phi(m) ? b : b % phi(m) + phi(m)) mod m. Works for ANY a, m, even non-coprime.
#include <bits/stdc++.h>
using namespace std;

long long phi(long long n) {
    long long res = n;
    for (long long i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            while (n % i == 0) n /= i;
            res -= res / i;
        }
    }
    if (n > 1) res -= res / n;
    return res;
}

// Computes (base ^ exp) with mod flag: if >= mod, returns (val % mod) + mod
long long powerModWithFlag(long long base, long long exp, long long mod) {
    long long res = 1;
    bool over = false;
    if (base >= mod) { base %= mod; over = true; }
    while (exp > 0) {
        if (exp & 1) {
            res *= base;
            if (res >= mod) { res %= mod; over = true; }
        }
        base *= base;
        if (base >= mod) { base %= mod; over = true; }
        exp >>= 1;
    }
    return over ? res + mod : res;
}

// Solves a[i] ^ a[i+1] ^ ... ^ a[n-1] mod m
long long powerTower(const vector<long long>& a, int i, long long m) {
    if (i == (int)a.size() || m == 1) return 1;
    long long p = phi(m);
    long long exp = powerTower(a, i + 1, p);
    return powerModWithFlag(a[i], exp, m) % m;
}
