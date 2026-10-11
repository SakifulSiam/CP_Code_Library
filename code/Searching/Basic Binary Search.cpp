// lower_bound on a sorted vector: first index i with a[i] >= x, or n.
int firstAtLeast(const vector<long long>& a,long long x) {
    int l=0,r=a.size();
    while (l<r) { int mid=l+(r-l)/2; if (a[mid]<x) l=mid+1; else r=mid; }
    return l;
}

// Last true for a monotone predicate: P(l)=true, P(r)=false; returns l.
template<class Predicate>
long long lastTrue(long long l,long long r,Predicate P) {
    while (r-l>1) {
        long long mid=l+(r-l)/2;
        if (P(mid)) l=mid; else r=mid;
    }
    return l;
}

// Binary search on answer: find the minimum feasible value.
// Establish infeasible low and feasible high bounds before calling the loop.
template<class Predicate>
long long firstTrue(long long low,long long high,Predicate feasible) {
    while (high-low>1) {
        long long mid=low+(high-low)/2;
        if (feasible(mid)) high=mid; else low=mid;
    }
    return high;
}
