// Lowercase a-z trie.
struct Trie {
    struct Node { int next[26]; bool terminal=false; Node() { fill(next,next+26,-1); } };
    vector<Node> t{Node()};
    void insert(const string& s) {
        int v=0;
        for(char c:s) { int x=c-'a'; if(t[v].next[x]==-1) { t[v].next[x]=t.size(); t.emplace_back(); } v=t[v].next[x]; }
        t[v].terminal=true;
    }
    bool contains(const string& s) const {
        int v=0;
        for(char c:s) { int x=c-'a'; if(t[v].next[x]==-1) return false; v=t[v].next[x]; }
        return t[v].terminal;
    }
};
