// For equally likely outcomes: P(A)=favorable/total; conditional P(A|B)=P(A and B)/P(B).
// Linearity: E[X]=sum E[I_i] for indicator variables, even when dependent.
// Variance: E[X^2] - E[X]^2; independent variables have additive variances.
double probability(int favorable,long long total){return (double)favorable/total;}

// Expected DP on an acyclic state graph, evaluated in reverse topological order.
// E[u] = immediateCost + sum(probability(u->v) * E[v]); terminal states have E=0.
double expectedFromTransitions(double cost,const vector<pair<double,double>>& nextStateExpected) {
    double e=cost; for(auto [p,nextE]:nextStateExpected)e+=p*nextE; return e;
}
// Self-referential expectation example: fair coin until HH.
// E0=1+(E0+E1)/2, E1=1+E0/2; solving gives E0=6 tosses.
// Cyclic expectation states require solving a linear system; naive recursion loops.
