// Formula reference: see the PDF Random section (10) for Catalan, Stirling, derangements, and number-theory identities.
// Factorials and nCr modulo prime MOD. Requires n < MOD.
const long long MOD = 1000000007;
long long modPow(long long a, long long e) {
    long long r = 1;
    for (; e; e >>= 1, a = a * a % MOD) if (e & 1) r = r * a % MOD;
    return r;
}
struct Combinatorics {
    vector<long long> fact, invFact;
    Combinatorics(int n) : fact(n + 1), invFact(n + 1) {
        fact[0] = 1;
        for (int i = 1; i <= n; ++i) fact[i] = fact[i-1] * i % MOD;
        invFact[n] = modPow(fact[n], MOD - 2);
        for (int i = n; i; --i) invFact[i-1] = invFact[i] * i % MOD;
    }
    long long nCr(int n, int r) const {
        if (r < 0 || r > n) return 0;
        return fact[n] * invFact[r] % MOD * invFact[n-r] % MOD;
    }
    long long nPr(int n, int r) const { return r < 0 || r > n ? 0 : fact[n] * invFact[n-r] % MOD; }
};

// Stars and bars: ways to distribute n identical items into k nonempty groups = C(n-1,k-1).
// Derangements: D[0]=1, D[1]=0, D[n]=(n-1)(D[n-1]+D[n-2]).
// Catalan: C[n]=C(2n,n)/(n+1), valid modulo prime when factorial range is supported.
// Stirling 2nd kind: S(n,k)=k*S(n-1,k)+S(n-1,k-1), S(0,0)=1.
// Code: vector<vector<long long>> S(n+1,vector<long long>(k+1)); S[0][0]=1;
// for i=1..n, j=1..min(i,k): S[i][j]=(j*S[i-1][j]+S[i-1][j-1]) % MOD.
// PIE: count union = sum(nonempty subsets A) (-1)^(|A|+1) count(intersection A).
// Probability: favorable/total; conditional P(A|B)=P(A and B)/P(B). Variance: Var(X)=E[X^2] - (E[X])^2.
// Expected value: E[X]=sum_i E[X_i] (linearity holds even if dependent). Coupon collector: n * H_n.
// DAG transitions: E[u] = cost + sum(p_v * E[v]); cyclic states require Gaussian elimination (see Expected Value DP).
// Indicator trick: write count as sum of 0/1 indicators, then take expectations.
