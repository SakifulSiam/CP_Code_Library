// Sprague-Grundy Theorem: mex calculation, DAG games, and subtraction game.
// An impartial game under normal play is winning iff XOR sum of Grundy values != 0.
#include <bits/stdc++.h>
using namespace std;

// 1. Minimum Excluded Value (mex)
int getMex(const vector<int>& vals) {
    vector<bool> seen(vals.size() + 2, false);
    for (int x : vals) if (x < (int)seen.size()) seen[x] = true;
    for (int i = 0; ; ++i) if (!seen[i]) return i;
}

// 2. Subtraction Game: from state n, player can subtract any s in allowed moves S
vector<int> subtractionGameGrundy(int maxN, const vector<int>& S) {
    vector<int> G(maxN + 1, 0);
    for (int n = 1; n <= maxN; ++n) {
        vector<int> nextStates;
        for (int s : S) if (n >= s) nextStates.push_back(G[n - s]);
        G[n] = getMex(nextStates);
    }
    return G;
}

// 3. Generic DAG Game Grundy values (memoized)
int memoG[100005];
int getGrundy(int u, const vector<vector<int>>& adj) {
    if (memoG[u] != -1) return memoG[u];
    vector<int> transitions;
    for (int v : adj[u]) transitions.push_back(getGrundy(v, adj));
    return memoG[u] = getMex(transitions);
}
