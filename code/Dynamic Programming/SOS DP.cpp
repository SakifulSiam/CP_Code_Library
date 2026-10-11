// WHEN: aggregate a function over all submasks/supermasks. TIME: O(k*2^k). ASSUMES: k is small enough for 2^k memory.
// Subset zeta transform: after this, f[mask] = sum of original f[sub] over sub subset of mask.
void subsetZeta(vector<long long>& f,int bits) {
    for(int b=0;b<bits;++b) for(int mask=0;mask<(1<<bits);++mask)
        if(mask>>b&1) f[mask]+=f[mask^(1<<b)];
}
// Superset zeta: f[mask] becomes sum of original f[sup] where sup contains mask.
void supersetZeta(vector<long long>& f,int bits) {
    for(int b=0;b<bits;++b) for(int mask=0;mask<(1<<bits);++mask)
        if(!(mask>>b&1)) f[mask]+=f[mask|(1<<b)];
}
