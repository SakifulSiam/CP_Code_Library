// Monotonic Stack & Queue: O(n) next greater, histogram largest rectangle, sliding window min/max
#include <bits/stdc++.h>
using namespace std;

// 1. Next Greater Element: returns index of next strictly greater element (or n if none)
vector<int> nextGreater(const vector<int>& a) {
    int n = a.size();
    vector<int> nxt(n, n);
    vector<int> st; // stores indices with decreasing values
    for (int i = 0; i < n; ++i) {
        while (!st.empty() && a[st.back()] < a[i]) {
            nxt[st.back()] = i;
            st.pop_back();
        }
        st.push_back(i);
    }
    return nxt;
}

// 2. Largest Rectangle in Histogram: O(n)
long long largestRectangleArea(const vector<long long>& h) {
    int n = h.size();
    vector<int> st;
    long long maxArea = 0;
    for (int i = 0; i <= n; ++i) {
        long long cur = (i == n ? 0 : h[i]);
        while (!st.empty() && h[st.back()] >= cur) {
            long long height = h[st.back()];
            st.pop_back();
            int width = st.empty() ? i : i - st.back() - 1;
            maxArea = max(maxArea, height * width);
        }
        st.push_back(i);
    }
    return maxArea;
}

// 3. Sliding Window Maximum for window size k in O(n)
vector<int> slidingWindowMax(const vector<int>& a, int k) {
    deque<int> dq; // stores indices with decreasing values
    vector<int> ans;
    for (int i = 0; i < (int)a.size(); ++i) {
        if (!dq.empty() && dq.front() <= i - k) dq.pop_front();
        while (!dq.empty() && a[dq.back()] <= a[i]) dq.pop_back();
        dq.push_back(i);
        if (i >= k - 1) ans.push_back(a[dq.front()]);
    }
    return ans;
}
