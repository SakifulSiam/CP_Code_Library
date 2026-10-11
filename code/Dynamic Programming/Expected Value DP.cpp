// Example state equations: expected coin tosses until two consecutive heads.
// State 0: previous toss is not H; state 1: previous toss is H; state 2 is terminal.
// E0=1+(E0+E1)/2 and E1=1+E0/2, so E0=6 and E1=4.
pair<double,double> expectedTossesForHH(){return {6.0,4.0};}
// For a finite acyclic process, fill E[state] from terminal states backward using
// E[s] = immediate_cost + sum(P(s->t) * E[t]). For cyclic transitions solve equations.

// Gaussian elimination for cyclic Markov expectation equations.
vector<double> solveLinearSystem(vector<vector<double>> a) { // augmented n x (n+1)
    int n=a.size();
    for(int col=0,row=0;col<n&&row<n;++col) {
        int pivot=row; for(int i=row+1;i<n;++i)if(abs(a[i][col])>abs(a[pivot][col]))pivot=i;
        if(abs(a[pivot][col])<1e-12)continue;
        swap(a[pivot],a[row]); double div=a[row][col];
        for(int j=col;j<=n;++j)a[row][j]/=div;
        for(int i=0;i<n;++i)if(i!=row){double factor=a[i][col];for(int j=col;j<=n;++j)a[i][j]-=factor*a[row][j];}
        ++row;
    }
    vector<double> x(n); for(int i=0;i<n;++i)x[i]=a[i][n]; return x;
}
// Build one equation per nonterminal state: E[u] - sum(P(u->v)*E[v]) = 1.
// Include only nonterminal v terms; terminal states have expectation 0.
