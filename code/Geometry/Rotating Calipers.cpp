// Diameter (farthest pair) of a convex polygon in CCW order, O(n).
// Use the convexHull template first; squared distances avoid floating point.
long long dist2(Point a,Point b) {
    long long dx=a.x-b.x, dy=a.y-b.y; return dx*dx+dy*dy;
}
long long convexDiameter2(const vector<Point>& p) {
    int n=p.size();
    if (n<=1) return 0;
    if (n==2) return dist2(p[0],p[1]);
    auto area2=[&](int i,int j,int k){ return llabs(cross(p[i],p[j],p[k])); };
    long long best=0;
    for (int i=0,j=1;i<n;++i) {
        int ni=(i+1)%n;
        while (area2(i,ni,(j+1)%n)>area2(i,ni,j)) j=(j+1)%n;
        best=max({best,dist2(p[i],p[j]),dist2(p[ni],p[j])});
    }
    return best;
}
