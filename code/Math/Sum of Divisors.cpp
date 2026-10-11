// Sum of positive divisors of n from prime factorization: n=product p^e.
long long sumDivisors(long long n) {
    long long answer=1;
    for(long long p=2;p<=n/p;++p) if(n%p==0) {
        long long term=1, power=1;
        while(n%p==0) { n/=p; power*=p; term+=power; }
        answer*=term;
    }
    if(n>1) answer*=1+n;
    return answer;
}
// May overflow long long; use __int128 or modular arithmetic for large answers.
