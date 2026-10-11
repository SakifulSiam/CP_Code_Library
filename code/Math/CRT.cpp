// Merge x=a (mod m), x=b (mod n), including non-coprime moduli.
long long extendedGcdCRT(long long a,long long b,long long& x,long long& y) {
    if(!b) { x=1; y=0; return a; }
    long long x1,y1,g=extendedGcdCRT(b,a%b,x1,y1);
    x=y1; y=x1-(a/b)*y1; return g;
}
// Returns {residue, modulus}; modulus 0 means no solution. Intermediate products must fit.
pair<long long,long long> mergeCRT(long long a,long long m,long long b,long long n) {
    long long x,y,g=extendedGcdCRT(m,n,x,y), diff=b-a;
    if(diff%g) return {0,0};
    long long mod=n/g;
    __int128 k=(__int128)(diff/g)*x%mod;
    long long lcm=m*mod;
    long long r=(long long)(((__int128)a+(__int128)m*k)%lcm);
    if(r<0) r+=lcm;
    return {r,lcm};
}
