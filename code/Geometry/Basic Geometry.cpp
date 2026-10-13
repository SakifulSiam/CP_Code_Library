// WHEN: orientation, segment intersection, and polygon area. TIME: O(1) per primitive, O(n) area.
// Shared 2D Point structure with long long coordinates.
struct Point {
    long long x, y;
    bool operator<(const Point& o) const { return tie(x, y) < tie(o.x, o.y); }
    bool operator==(const Point& o) const { return x == o.x && y == o.y; }
    Point operator+(const Point& o) const { return {x + o.x, y + o.y}; }
    Point operator-(const Point& o) const { return {x - o.x, y - o.y}; }
};
long long cross(Point a, Point b) { return a.x * b.y - a.y * b.x; }
long long cross(Point a, Point b, Point c) { return cross(b - a, c - a); }
long long dot(Point a, Point b) { return a.x * b.x + a.y * b.y; }
long long dist2(Point a, Point b) { return dot(a - b, a - b); }
long long orient(Point a, Point b, Point c) { return cross(a, b, c); }

bool onSegment(Point a, Point b, Point p) {
    return orient(a, b, p) == 0 && min(a.x, b.x) <= p.x && p.x <= max(a.x, b.x)
        && min(a.y, b.y) <= p.y && p.y <= max(a.y, b.y);
}
bool segmentsIntersect(Point a, Point b, Point c, Point d) {
    long long x = orient(a, b, c), y = orient(a, b, d), z = orient(c, d, a), w = orient(c, d, b);
    if (x == 0 && onSegment(a, b, c)) return true;
    if (y == 0 && onSegment(a, b, d)) return true;
    if (z == 0 && onSegment(c, d, a)) return true;
    if (w == 0 && onSegment(c, d, b)) return true;
    return (x < 0) != (y < 0) && (z < 0) != (w < 0);
}
long long doubledPolygonArea(const vector<Point>& p) {
    long long area = 0; int n = p.size();
    for (int i = 0; i < n; ++i) area += cross(p[i], p[(i + 1) % n]);
    return llabs(area); // shoelace formula; actual area is area / 2.0
}
