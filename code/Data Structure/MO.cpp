// Static range queries. Implement add/remove to maintain the desired answer.
struct Query { int l, r, id; };
vector<long long> moQueries(const vector<int>& a, vector<Query> qs) {
    int n = a.size(), block = max(1, (int)sqrt(n));
    sort(qs.begin(), qs.end(), [&](const Query& x, const Query& y) {
        int bx = x.l / block, by = y.l / block;
        return bx == by ? ((bx & 1) ? x.r > y.r : x.r < y.r) : bx < by;
    });
    vector<long long> ans(qs.size());
    int L = 0, R = -1; long long cur = 0;
    auto add = [&](int i) { cur += a[i]; };
    auto remove = [&](int i) { cur -= a[i]; };
    for (auto q : qs) {
        while (L > q.l) add(--L);
        while (R < q.r) add(++R);
        while (L < q.l) remove(L++);
        while (R > q.r) remove(R--);
        ans[q.id] = cur;
    }
    return ans;
}
