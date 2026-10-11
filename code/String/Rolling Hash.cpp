// WHEN: compare substrings quickly. TIME: O(n) build and O(1) query. ASSUMES: hashes are probabilistic; double hash greatly lowers but does not remove collision risk.
// One modular polynomial hash for substring equality; use two moduli when collisions matter.
struct RollingHash {
    static const long long MOD = 1000000007, BASE = 911382323;
    vector<long long> h, power;
    RollingHash(const string& s) : h(s.size()+1), power(s.size()+1,1) {
        for(int i=0;i<(int)s.size();++i) {
            power[i+1]=power[i]*BASE%MOD;
            h[i+1]=(h[i]*BASE+(unsigned char)s[i]+1)%MOD;
        }
    }
    long long get(int l,int r) const { // [l,r)
        long long x=(h[r]-h[l]*power[r-l])%MOD;
        return (x+MOD)%MOD;
    }
};

// Double polynomial hash for substring equality; query ranges are [l,r).
struct DoubleRollingHash {
    static const long long MOD1=1000000007, MOD2=1000000009, BASE=911382323;
    vector<long long> h1,h2,p1,p2;
    DoubleRollingHash(const string& s):h1(s.size()+1),h2(s.size()+1),p1(s.size()+1,1),p2(s.size()+1,1){
        for(int i=0;i<(int)s.size();++i){
            long long x=(unsigned char)s[i]+1;
            p1[i+1]=p1[i]*BASE%MOD1;p2[i+1]=p2[i]*BASE%MOD2;
            h1[i+1]=(h1[i]*BASE+x)%MOD1;h2[i+1]=(h2[i]*BASE+x)%MOD2;
        }
    }
    pair<long long,long long> get(int l,int r)const{
        long long a=(h1[r]-h1[l]*p1[r-l])%MOD1,b=(h2[r]-h2[l]*p2[r-l])%MOD2;
        if(a<0)a+=MOD1;if(b<0)b+=MOD2;return {a,b};
    }
};
