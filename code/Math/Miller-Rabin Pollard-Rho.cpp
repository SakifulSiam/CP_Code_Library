// Deterministic primality test and factorization for 64-bit unsigned integers.
using u64 = unsigned long long;
using u128 = __uint128_t;
u64 mulMod(u64 a,u64 b,u64 mod) { return (u128)a*b%mod; }
u64 powMod64(u64 a,u64 e,u64 mod) {
    u64 r=1;
    for (;e;e>>=1,a=mulMod(a,a,mod)) if (e&1) r=mulMod(r,a,mod);
    return r;
}
bool isPrime64(u64 n) {
    if (n<2) return false;
    for (u64 p:{2ULL,3ULL,5ULL,7ULL,11ULL,13ULL,17ULL,19ULL,23ULL,29ULL,31ULL,37ULL}) {
        if (n%p==0) return n==p;
    }
    u64 d=n-1, s=0; while (!(d&1)) d>>=1,++s;
    for (u64 a:{2ULL,325ULL,9375ULL,28178ULL,450775ULL,9780504ULL,1795265022ULL}) {
        if (a%n==0) continue;
        u64 x=powMod64(a%n,d,n);
        if (x==1 || x==n-1) continue;
        bool composite=true;
        for (int r=1;r<s;++r) { x=mulMod(x,x,n); if (x==n-1) { composite=false; break; } }
        if (composite) return false;
    }
    return true;
}
auto seedClock = chrono::steady_clock::now();
mt19937_64 rng64(seedClock.time_since_epoch().count());
u64 pollardRho(u64 n) {
    if (n%2==0) return 2;
    if (n%3==0) return 3;
    while (true) {
        u64 c=rng64()%(n-1)+1, x=rng64()%(n-2)+2, y=x, d=1;
        auto f=[&](u64 v){ return (u64)(((u128)mulMod(v,v,n)+c)%n); };
        while (d==1) { x=f(x); y=f(f(y)); d=gcd(x>y?x-y:y-x,n); }
        if (d!=n) return d;
    }
}
void factor64(u64 n,map<u64,int>& factors) {
    if (n==1) return;
    if (isPrime64(n)) { ++factors[n]; return; }
    u64 d=pollardRho(n);
    factor64(d,factors); factor64(n/d,factors);
}
