// Longest palindromic substring length in O(n).
int longestPalindrome(const string& s) {
    string t="^";
    for(char c:s) t += string("#") + c;
    t += "#$";
    vector<int> p(t.size()); int center=0,right=0,best=0;
    for(int i=1;i+1<(int)t.size();++i) {
        int mirror=2*center-i;
        if(i<right) p[i]=min(right-i,p[mirror]);
        while(t[i+1+p[i]]==t[i-1-p[i]]) ++p[i];
        if(i+p[i]>right) center=i,right=i+p[i];
        best=max(best,p[i]);
    }
    return best;
}
