// Monotonic chain hull, O(n log n). Removes collinear interior points.
struct Point { long long x,y; bool operator<(const Point& o) const { return tie(x,y)<tie(o.x,o.y); } };
long long cross(Point a,Point b,Point c) {
    return (b.x-a.x)*(c.y-a.y)-(b.y-a.y)*(c.x-a.x);
}
vector<Point> convexHull(vector<Point> p) {
    sort(p.begin(),p.end()); p.erase(unique(p.begin(),p.end(),[](auto a,auto b){return a.x==b.x&&a.y==b.y;}),p.end());
    if (p.size()<=1) return p;
    vector<Point> h;
    for (auto x:p) { while (h.size()>=2 && cross(h[h.size()-2],h.back(),x)<=0) h.pop_back(); h.push_back(x); }
    int lower=h.size();
    for (int i=(int)p.size()-2;i>=0;--i) { auto x=p[i]; while ((int)h.size()>lower && cross(h[h.size()-2],h.back(),x)<=0) h.pop_back(); h.push_back(x); }
    h.pop_back(); return h; // counterclockwise; for all-collinear input, returns endpoints.
}
