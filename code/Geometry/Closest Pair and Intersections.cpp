// Closest Pair of Points, Point in Polygon, and Line/Circle Intersection
#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-9;

// 1. Closest Pair of Points: O(n log n) sweep-line
struct Pt {
    long long x, y; int id;
    bool operator<(const Pt& o) const { return x != o.x ? x < o.x : y < o.y; }
};
long long dist2(Pt a, Pt b) { return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y); }

pair<Pt, Pt> closestPair(vector<Pt> pts) {
    sort(pts.begin(), pts.end());
    struct CmpY { bool operator()(const Pt& a, const Pt& b) const { return a.y != b.y ? a.y < b.y : a.x < b.x; } };
    set<Pt, CmpY> active;
    long long bestD2 = LLONG_MAX;
    pair<Pt, Pt> bestPair;
    int left = 0;
    for (const auto& p : pts) {
        while (left < (int)pts.size() && 1LL * (p.x - pts[left].x) * (p.x - pts[left].x) >= bestD2) {
            active.erase(pts[left++]);
        }
        long long d = ceil(sqrt(bestD2));
        auto it1 = active.lower_bound({p.x, p.y - d, -1});
        auto it2 = active.upper_bound({p.x, p.y + d, -1});
        for (auto it = it1; it != it2; ++it) {
            long long d2 = dist2(p, *it);
            if (d2 < bestD2) { bestD2 = d2; bestPair = {p, *it}; }
        }
        active.insert(p);
    }
    return bestPair;
}

// 2. Point in Polygon: -1: outside, 0: on boundary, 1: strictly inside
struct Point2D { long long x, y; };
long long cross(Point2D a, Point2D b, Point2D c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}
int pointInPolygon(Point2D p, const vector<Point2D>& poly) {
    int n = poly.size(), winding = 0;
    for (int i = 0; i < n; ++i) {
        Point2D a = poly[i], b = poly[(i + 1) % n];
        if (min(a.x, b.x) <= p.x && p.x <= max(a.x, b.x) &&
            min(a.y, b.y) <= p.y && p.y <= max(a.y, b.y) && cross(a, b, p) == 0) return 0;
        if (a.y <= p.y) {
            if (b.y > p.y && cross(a, b, p) > 0) winding++;
        } else {
            if (b.y <= p.y && cross(a, b, p) < 0) winding--;
        }
    }
    return winding != 0 ? 1 : -1;
}

// 3. Line and Circle Intersection: circle centered at (0, 0) with radius r, line Ax + By + C = 0
// For general circle (cx, cy), translate line by C' = C + A*cx + B*cy.
vector<pair<double, double>> lineCircleIntersection(double r, double A, double B, double C) {
    double dist0 = abs(C) / sqrt(A * A + B * B);
    if (dist0 > r + EPS) return {}; // No intersection
    double x0 = -A * C / (A * A + B * B), y0 = -B * C / (A * A + B * B);
    if (abs(dist0 - r) < EPS) return {{x0, y0}}; // Tangent
    double d = sqrt(max(0.0, r * r - dist0 * dist0));
    double mult = sqrt(d * d / (A * A + B * B));
    return {{x0 + B * mult, y0 - A * mult}, {x0 - B * mult, y0 + A * mult}};
}
