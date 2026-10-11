vector<int> prefixFunction(const string& s) {
    vector<int> pi(s.size());
    for(int i=1;i<(int)s.size();++i) {
        int j=pi[i-1];
        while(j>0 && s[i]!=s[j]) j=pi[j-1];
        if(s[i]==s[j]) ++j;
        pi[i]=j;
    }
    return pi;
}
vector<int> findMatches(const string& text,const string& pattern) {
    if(pattern.empty()) return {};
    string s=pattern+'#'+text; vector<int> pi=prefixFunction(s), matches;
    for(int i=(int)pattern.size()+1;i<(int)s.size();++i)
        if(pi[i]==(int)pattern.size()) matches.push_back(i-2*(int)pattern.size());
    return matches;
}
