// Suffix Automaton (SAM): O(n) construction and linear size DAG of all substrings.
#include <bits/stdc++.h>
using namespace std;

struct SuffixAutomaton {
    struct State {
        int len, link;
        map<char, int> next;
    };
    vector<State> st;
    int sz, last;

    SuffixAutomaton(int maxLen = 1) { init(maxLen); }
    void init(int maxLen = 1) {
        st.clear();
        st.resize(maxLen * 2);
        st[0].len = 0;
        st[0].link = -1;
        sz = 1;
        last = 0;
    }

    void extend(char c) {
        int cur = sz++;
        st[cur].len = st[last].len + 1;
        int p = last;
        while (p != -1 && !st[p].next.count(c)) {
            st[p].next[c] = cur;
            p = st[p].link;
        }
        if (p == -1) {
            st[cur].link = 0;
        } else {
            int q = st[p].next[c];
            if (st[p].len + 1 == st[q].len) {
                st[cur].link = q;
            } else {
                int clone = sz++;
                st[clone].len = st[p].len + 1;
                st[clone].next = st[q].next;
                st[clone].link = st[q].link;
                while (p != -1 && st[p].next[c] == q) {
                    st[p].next[c] = clone;
                    p = st[p].link;
                }
                st[q].link = st[cur].link = clone;
            }
        }
        last = cur;
    }

    // Number of distinct substrings in O(states)
    long long countDistinctSubstrings() const {
        long long total = 0;
        for (int i = 1; i < sz; ++i) total += st[i].len - st[st[i].link].len;
        return total;
    }
};
