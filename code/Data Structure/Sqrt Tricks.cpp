// Enumerate divisors in pairs up to sqrt(n), O(sqrt(n)).
vector<long long> divisors(long long n) {
    vector<long long> small, large;
    for(long long d=1;d<=n/d;++d) if(n%d==0) {
        small.push_back(d);
        if(d!=n/d) large.push_back(n/d);
    }
    reverse(large.begin(),large.end());
    small.insert(small.end(),large.begin(),large.end());
    return small;
}
// Group equal floor(n/i) values: ranges with the same quotient can be processed together.
template<class F> void forEqualQuotients(long long n,F process) {
    for(long long l=1,r;l<=n;l=r+1) { long long q=n/l; r=n/q; process(l,r,q); }
}
