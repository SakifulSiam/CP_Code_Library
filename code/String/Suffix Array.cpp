// Suffix array + Kasai LCP; O(n log^2 n) build, O(n) LCP.
struct SuffixArray {
    vector<int> sa, rank, lcp;
    explicit SuffixArray(const string& s) {
        int n=s.size(); sa.resize(n); rank.resize(n); iota(sa.begin(),sa.end(),0);
        for(int i=0;i<n;++i) rank[i]=(unsigned char)s[i];
        vector<int> nextRank(n);
        for(int k=1;k<n;k*=2) {
            sort(sa.begin(),sa.end(),[&](int a,int b) {
                if(rank[a]!=rank[b]) return rank[a]<rank[b];
                return (a+k<n?rank[a+k]:-1)<(b+k<n?rank[b+k]:-1);
            });
            if(n) nextRank[sa[0]]=0;
            for(int i=1;i<n;++i) {
                int a=sa[i-1],b=sa[i];
                nextRank[b]=nextRank[a]+(rank[a]!=rank[b] || (a+k<n?rank[a+k]:-1)!=(b+k<n?rank[b+k]:-1));
            }
            rank.swap(nextRank);
            if(n && rank[sa[n-1]]==n-1) break;
        }
        vector<int> pos(n); for(int i=0;i<n;++i) pos[sa[i]]=i;
        lcp.assign(max(0,n-1),0); int h=0;
        for(int i=0;i<n;++i) {
            int r=pos[i]; if(r==n-1) { h=0; continue; }
            int j=sa[r+1]; while(i+h<n && j+h<n && s[i+h]==s[j+h]) ++h;
            lcp[r]=h; if(h) --h;
        }
    }
};
