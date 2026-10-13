// Monotonic chain convex hull, O(n log n). CCW order without collinear points.
// Uses shared Point struct and cross(a, b, c) from Basic Geometry.
vector<Point> convexHull(vector<Point> p) {
    sort(p.begin(), p.end());
    p.erase(unique(p.begin(), p.end()), p.end());
    if (p.size() <= 1) return p;
    vector<Point> h;
    for (auto& pt : p) {
        while (h.size() >= 2 && cross(h[h.size() - 2], h.back(), pt) <= 0) h.pop_back();
        h.push_back(pt);
    }
    int lower = h.size();
    for (int i = (int)p.size() - 2; i >= 0; --i) {
        auto& pt = p[i];
        while ((int)h.size() > lower && cross(h[h.size() - 2], h.back(), pt) <= 0) h.pop_back();
        h.push_back(pt);
    }
    h.pop_back();
    return h; // Returns counterclockwise hull vertices
}
