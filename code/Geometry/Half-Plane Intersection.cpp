// Half-Plane Intersection: O(n log n). Half-plane is the left side of directed line p -> p + v.
#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-9;

struct Vec {
    double x, y;
    Vec(double x = 0, double y = 0) : x(x), y(y) {}
    Vec operator+(const Vec& o) const { return {x + o.x, y + o.y}; }
    Vec operator-(const Vec& o) const { return {x - o.x, y - o.y}; }
    Vec operator*(double k) const { return {x * k, y * k}; }
    double cross(const Vec& o) const { return x * o.y - y * o.x; }
};

struct Line {
    Vec p, v; double ang;
    Line() {}
    Line(Vec p, Vec v) : p(p), v(v), ang(atan2(v.y, v.x)) {}
    bool operator<(const Line& o) const { return ang < o.ang; }
};

Vec lineIntersection(const Line& a, const Line& b) {
    Vec u = a.p - b.p;
    double t = b.v.cross(u) / a.v.cross(b.v);
    return a.p + a.v * t;
}

bool onLeft(const Line& l, const Vec& pt) {
    return l.v.cross(pt - l.p) > EPS;
}

// Returns convex polygon formed by intersection of half-planes (or empty if unbounded/empty)
vector<Vec> halfPlaneIntersection(vector<Line> lines) {
    // Add large bounding box if needed: [-INF, INF]
    sort(lines.begin(), lines.end());
    vector<Line> q(lines.size() + 5);
    int head = 0, tail = 0;
    q[0] = lines[0];

    for (int i = 1; i < (int)lines.size(); ++i) {
        while (head < tail && !onLeft(lines[i], lineIntersection(q[tail], q[tail - 1]))) tail--;
        while (head < tail && !onLeft(lines[i], lineIntersection(q[head], q[head + 1]))) head++;
        if (abs(lines[i].v.cross(q[tail].v)) < EPS) {
            if (onLeft(lines[i], q[tail].p)) q[tail] = lines[i];
        } else {
            q[++tail] = lines[i];
        }
    }
    while (head < tail && !onLeft(q[head], lineIntersection(q[tail], q[tail - 1]))) tail--;
    while (head < tail && !onLeft(q[tail], lineIntersection(q[head], q[head + 1]))) head++;
    if (tail - head <= 1) return {};

    vector<Vec> poly;
    for (int i = head; i < tail; ++i) poly.push_back(lineIntersection(q[i], q[i + 1]));
    poly.push_back(lineIntersection(q[tail], q[head]));
    return poly;
}
