// Sieve of Eratosthenes
// O(n log log n)
vector<bool> isPrime(n + 1, true);
isPrime[0] = isPrime[1] = false;
for(int i = 2; i * i <= n; i++)
    if(isPrime[i])
        for(int j = i * i; j <= n; j += i)
            isPrime[j] = false;


// Sieve + Smallest Prime Factor (SPF)
// O(n log log n)
vector<int> spf(n + 1);
for(int i = 0; i <= n; i++)
    spf[i] = i;
for(int i = 2; i * i <= n; i++)
    if(spf[i] == i)
        for(int j = i * i; j <= n; j += i)
            if(spf[j] == j)
                spf[j] = i;