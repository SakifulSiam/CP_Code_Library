// Lyndon Factorization, Minimal String Rotation, and Mersenne 61-bit Hash (2^61 - 1)
#include <bits/stdc++.h>
using namespace std;

// 1. Duval's Algorithm: O(n) Lyndon factorization of string s into s = w_1 w_2 ... w_k where w_1 >= ... >= w_k
vector<string> duval(const string& s) {
    int n = s.size(), i = 0;
    vector<string> factorization;
    while (i < n) {
        int j = i + 1, k = i;
        while (j < n && s[k] <= s[j]) {
            if (s[k] < s[j]) k = i;
            else k++;
            j++;
        }
        while (i <= k) {
            factorization.push_back(s.substr(i, j - k));
            i += j - k;
        }
    }
    return factorization;
}

// 2. Lexicographically Minimal String Rotation in O(n) (Booth's Algorithm)
int minRotation(string s) {
    s += s;
    int n = s.size(), i = 0, ans = 0;
    while (i < n / 2) {
        ans = i;
        int j = i + 1, k = i;
        while (j < n && s[k] <= s[j]) {
            if (s[k] < s[j]) k = i;
            else k++;
            j++;
        }
        while (i <= k) i += j - k;
    }
    return ans; // 0-based starting index in original string
}

// 3. Fast 61-bit Rolling Hash modulo Mersenne prime 2^61 - 1 (unhackable, O(1) query)
struct Hash61 {
    static const uint64_t MOD = (1ULL << 61) - 1;
    static uint64_t mulMod(uint64_t a, uint64_t b) {
        __uint128_t prod = (__uint128_t)a * b;
        uint64_t res = (prod >> 61) + (prod & MOD);
        if (res >= MOD) res -= MOD;
        return res;
    }
    uint64_t BASE;
    vector<uint64_t> h, p;
    Hash61(const string& s) : h(s.size() + 1, 0), p(s.size() + 1, 1) {
        mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
        BASE = uniform_int_distribution<uint64_t>(300, MOD - 2)(rng) | 1;
        for (int i = 0; i < (int)s.size(); ++i) {
            p[i + 1] = mulMod(p[i], BASE);
            h[i + 1] = mulMod(h[i], BASE) + (unsigned char)s[i] + 1;
            if (h[i + 1] >= MOD) h[i + 1] -= MOD;
        }
    }
    uint64_t get(int l, int r) const { // [l, r)
        uint64_t res = h[r] + MOD - mulMod(h[l], p[r - l]);
        return res >= MOD ? res - MOD : res;
    }
};
