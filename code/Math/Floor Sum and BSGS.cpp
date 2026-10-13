// Floor Sum, Primitive Root, and Baby-Step Giant-Step (BSGS)
#include <bits/stdc++.h>
using namespace std;

// 1. Floor Sum: sum_{i=0}^{n-1} floor((a * i + b) / m) in O(log(n + m)). AtCoder Library.
long long floorSum(long long n, long long m, long long a, long long b) {
    long long ans = 0;
    if (a >= m) { ans += (n - 1) * n / 2 * (a / m); a %= m; }
    if (b >= m) { ans += n * (b / m); b %= m; }
    long long yMax = (a * n + b) / m, xMax = yMax * m - b;
    if (yMax == 0) return ans;
    ans += (n - (xMax + a - 1) / a) * yMax;
    ans += floorSum(yMax, a, m, (a - xMax % a) % a);
    return ans;
}

// 2. Primitive Root: smallest generator modulo prime p
long long modPow(long long a, long long b, long long mod) {
    long long res = 1; a %= mod;
    for (; b; b >>= 1, a = a * a % mod) if (b & 1) res = res * a % mod;
    return res;
}
int primitiveRoot(int p) {
    vector<int> fact;
    int phi = p - 1, n = phi;
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            fact.push_back(i);
            while (n % i == 0) n /= i;
        }
    }
    if (n > 1) fact.push_back(n);
    for (int res = 2; res <= p; ++res) {
        bool ok = true;
        for (int factor : fact) {
            if (modPow(res, phi / factor, p) == 1) { ok = false; break; }
        }
        if (ok) return res;
    }
    return -1;
}

// 3. Baby-Step Giant-Step (BSGS): solve a^x = b (mod m) for coprime a, m in O(sqrt(m))
long long bsgs(long long a, long long b, long long m) {
    a %= m; b %= m;
    long long n = sqrt(m) + 1;
    unordered_map<long long, long long> vals;
    long long cur = 1;
    for (long long p = 0; p <= n; ++p) {
        vals[cur * b % m] = p;
        cur = cur * a % m;
    }
    long long an = cur; // a^n
    cur = 1;
    for (long long q = 1; q <= n; ++q) {
        cur = cur * an % m;
        if (vals.count(cur)) {
            long long ans = q * n - vals[cur];
            return ans;
        }
    }
    return -1; // no solution
}
