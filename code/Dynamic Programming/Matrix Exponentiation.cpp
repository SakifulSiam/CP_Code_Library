// Fibonacci in O(log n); adapt matrix and multiplication for a linear recurrence.
using Matrix = vector<vector<long long>>;
const long long MOD = 1000000007;
Matrix multiply(const Matrix& a,const Matrix& b) {
    int n=a.size(); Matrix c(n,vector<long long>(n));
    for(int i=0;i<n;++i) for(int k=0;k<n;++k) for(int j=0;j<n;++j)
        c[i][j]=(c[i][j]+a[i][k]*b[k][j])%MOD;
    return c;
}
Matrix power(Matrix a,long long e) {
    int n=a.size(); Matrix r(n,vector<long long>(n));
    for(int i=0;i<n;++i) r[i][i]=1;
    for(;e;e>>=1,a=multiply(a,a)) if(e&1) r=multiply(r,a);
    return r;
}
long long fibonacci(long long n) {
    if(n==0) return 0;
    Matrix base={{1,1},{1,0}};
    return power(base,n-1)[0][0];
}
