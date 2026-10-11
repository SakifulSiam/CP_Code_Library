// Euler phi and Mobius values for every x <= n, linear sieve O(n).
vector<int> phiMobiusSieve(int n, vector<int>& mu) {
    vector<int> phi(n+1), lp(n+1), primes; mu.assign(n+1,0);
    if(n>=1) phi[1]=mu[1]=1;
    for(int i=2;i<=n;++i) {
        if(!lp[i]) { lp[i]=i; primes.push_back(i); phi[i]=i-1; mu[i]=-1; }
        for(int p:primes) {
            if(p>lp[i] || 1LL*i*p>n) break;
            lp[i*p]=p;
            if(i%p==0) { phi[i*p]=phi[i]*p; mu[i*p]=0; break; }
            phi[i*p]=phi[i]*(p-1); mu[i*p]=-mu[i];
        }
    }
    return phi;
}
long long eulerPhi(long long n) {
    long long result=n;
    for(long long p=2;p*p<=n;++p) if(n%p==0) {
        while(n%p==0) n/=p;
        result-=result/p;
    }
    if(n>1) result-=result/n;
    return result;
}
