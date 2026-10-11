// Count pairs from two arrays with each exact gcd. O(V log V), V=max value.
// divisors[d] counts pairs where both values are divisible by d.
vector<long long> exactGcdPairs(const vector<int>& a,const vector<int>& b,int maxValue) {
    vector<long long> ca(maxValue+1), cb(maxValue+1), exact(maxValue+1);
    for (int x:a) ++ca[x];
    for (int x:b) ++cb[x];
    for (int d=maxValue;d>=1;--d) {
        long long count=0;
        for (int x=d;x<=maxValue;x+=d) count+=ca[x];
        long long other=0;
        for (int x=d;x<=maxValue;x+=d) other+=cb[x];
        exact[d]=count*other;
        for (int x=2*d;x<=maxValue;x+=d) exact[d]-=exact[x];
    }
    return exact; // exact[d] counts ordered cross-array pairs with gcd exactly d.
}
