// Contest Template: compile flags, fast IO, debug macro, pb_ds ordered_set, custom hash, __int128, stress-test
// Compile: g++ -O2 -std=c++17 -Wall -Wextra -Wshadow -fsanitize=address,undefined -DLOCAL sol.cpp -o sol
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

using ll = long long;
using pii = pair<int, int>;

// 1. Policy Based Data Structure: Ordered Set
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
// .find_by_order(k): iterator to k-th smallest (0-indexed); .order_of_key(x): count strictly < x

// 2. Custom anti-hack hash for unordered_map / unordered_set
struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15ULL;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
        x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
        return x ^ (x >> 31);
    }
    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};
template <typename K, typename V> using safe_map = unordered_map<K, V, custom_hash>;

// 3. __int128 IO
void print128(__int128 x) {
    if (x < 0) { cout << '-'; x = -x; }
    if (x > 9) print128(x / 10);
    cout << (char)('0' + (x % 10));
}
__int128 read128() {
    __int128 x = 0; int f = 1; char ch = cin.get();
    while (!isdigit(ch)) { if (ch == '-') f = -1; ch = cin.get(); }
    while (isdigit(ch)) { x = x * 10 + ch - '0'; ch = cin.get(); }
    return x * f;
}

// 4. Debug macro
#ifdef LOCAL
#define dbg(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
void debug_out() { cerr << endl; }
template <typename Head, typename... Tail>
void debug_out(Head H, Tail... T) { cerr << " " << H; debug_out(T...); }
#else
#define dbg(...)
#endif

// 5. Stress test bash script:
// for((i=1;;i++)); do ./gen $i > in; ./sol < in > out1; ./brute < in > out2; diff -w out1 out2 || break; echo "Test $i OK"; done

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    // cin >> T;
    while (T--) {
        // solve();
    }
    return 0;
}
