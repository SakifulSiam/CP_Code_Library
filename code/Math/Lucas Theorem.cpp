// nCr modulo a prime p, even when n >= p. TIME: O(p + log_p n).
// Requires p small enough to precompute factorials up to p-1.
long long modPow(long long a,long long e,long long mod) {
    long long r=1;
    for (;e;e>>=1,a=a*a%mod) if (e&1) r=r*a%mod;
    return r;
}
long long chooseSmall(long long n,long long r,const vector<long long>& fact,long long p) {
    if (r<0 || r>n) return 0;
    return fact[n]*modPow(fact[r]*fact[n-r]%p,p-2,p)%p;
}
long long lucas(long long n,long long r,long long p,const vector<long long>& fact) {
    long long ans=1;
    while (n || r) {
        long long ni=n%p, ri=r%p;
        if (ri>ni) return 0;
        ans=ans*chooseSmall(ni,ri,fact,p)%p;
        n/=p; r/=p;
    }
    return ans;
}
