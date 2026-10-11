// Extended Euclid works for any modulus when gcd(a,m)=1.
long long extendedGcd(long long a,long long b,long long& x,long long& y) {
    if(!b) { x=1; y=0; return a; }
    long long x1,y1,g=extendedGcd(b,a%b,x1,y1);
    x=y1; y=x1-(a/b)*y1; return g;
}
long long modInverse(long long a,long long mod) {
    long long x,y,g=extendedGcd(a,mod,x,y);
    if(g!=1 && g!=-1) return -1; // no inverse
    x/=g;
    return (x%mod+mod)%mod;
}
// For prime MOD and a%MOD != 0: inverse = a^(MOD-2) mod MOD.
