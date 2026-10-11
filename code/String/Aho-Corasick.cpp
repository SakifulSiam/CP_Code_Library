// Lowercase a-z patterns; reports number of matches per pattern after scanning text.
struct AhoCorasick {
    struct Node { int next[26]; int link = 0; vector<int> out; Node() { fill(next,next+26,-1); } };
    vector<Node> t{Node()};
    void add(const string& s, int id) {
        int v=0; for(char c:s) { int x=c-'a'; if(t[v].next[x]==-1) { t[v].next[x]=t.size(); t.emplace_back(); } v=t[v].next[x]; }
        t[v].out.push_back(id);
    }
    void build() {
        queue<int> q;
        for(int c=0;c<26;++c) { int u=t[0].next[c]; if(u==-1) t[0].next[c]=0; else q.push(u); }
        while(!q.empty()) {
            int v=q.front(); q.pop();
            for(int id:t[t[v].link].out) t[v].out.push_back(id);
            for(int c=0;c<26;++c) {
                int u=t[v].next[c];
                if(u==-1) t[v].next[c]=t[t[v].link].next[c];
                else { t[u].link=t[t[v].link].next[c]; q.push(u); }
            }
        }
    }
    vector<int> countMatches(const string& text,int patternCount) const {
        vector<int> count(patternCount); int v=0;
        for(char c:text) { v=t[v].next[c-'a']; for(int id:t[v].out) ++count[id]; }
        return count;
    }
};
