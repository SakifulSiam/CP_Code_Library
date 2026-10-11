// Binary trie for nonnegative 31-bit values; increase the top bit if constraints require it.
struct BinaryTrie {
    struct Node { int child[2] = {-1, -1}; };
    vector<Node> t{{}};
    void insert(int x) {
        int v = 0;
        for (int b = 30; b >= 0; --b) {
            int bit = (x >> b) & 1;
            if (t[v].child[bit] == -1) { t[v].child[bit] = t.size(); t.push_back({}); }
            v = t[v].child[bit];
        }
    }
    int maxXor(int x) const {
        int v = 0, result = 0;
        for (int b = 30; b >= 0; --b) {
            int bit = (x >> b) & 1, want = bit ^ 1;
            if (t[v].child[want] != -1) { result |= 1 << b; v = t[v].child[want]; }
            else v = t[v].child[bit];
        }
        return result;
    }
};
// Max prefix-XOR versus suffix-XOR over every split (both sides nonempty).
int maxPrefixSuffixXor(const vector<int>& a) {
    int n=a.size(); if(n<2) return 0;
    vector<int> pref(n),suff(n); pref[0]=a[0];
    for(int i=1;i<n;++i) pref[i]=pref[i-1]^a[i];
    suff[n-1]=a[n-1]; for(int i=n-2;i>=0;--i) suff[i]=suff[i+1]^a[i];
    BinaryTrie trie; int answer=0;
    for(int split=0;split<n-1;++split) { trie.insert(pref[split]); answer=max(answer,trie.maxXor(suff[split+1])); }
    return answer;
}
