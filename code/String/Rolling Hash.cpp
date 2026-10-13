// Substring rolling hash with randomized base to prevent anti-hash test generation.
// O(n) build, O(1) query on [l, r).
static mt19937_64 hash_rng(chrono::steady_clock::now().time_since_epoch().count());
static const long long MOD1 = 1000000007, MOD2 = 1000000009;
static const long long BASE1 = uniform_int_distribution<long long>(300, MOD1 - 2)(hash_rng) | 1;
static const long long BASE2 = uniform_int_distribution<long long>(300, MOD2 - 2)(hash_rng) | 1;

struct RollingHash {
    vector<long long> h, power;
    long long mod, base;
    RollingHash(const string& s, long long mod = MOD1, long long base = BASE1)
        : h(s.size() + 1), power(s.size() + 1, 1), mod(mod), base(base) {
        for (int i = 0; i < (int)s.size(); ++i) {
            power[i + 1] = power[i] * base % mod;
            h[i + 1] = (h[i] * base + (unsigned char)s[i] + 1) % mod;
        }
    }
    long long get(int l, int r) const { // [l, r)
        long long x = (h[r] - h[l] * power[r - l]) % mod;
        return (x + mod) % mod;
    }
};

struct DoubleRollingHash {
    RollingHash rh1, rh2;
    DoubleRollingHash(const string& s) : rh1(s, MOD1, BASE1), rh2(s, MOD2, BASE2) {}
    pair<long long, long long> get(int l, int r) const {
        return {rh1.get(l, r), rh2.get(l, r)};
    }
};
