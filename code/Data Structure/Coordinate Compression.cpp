// WHEN: replace large ordered values with compact ranks. TIME: build O(n log n), lookup O(log n). ASSUMES: add all values before build; id is meaningful for values present in the list.
// Coordinate compression: preserves order while mapping values to [0..m-1].
template<class T>
struct Compressor {
    vector<T> values;
    void add(T x){values.push_back(x);}
    void build(){sort(values.begin(),values.end());values.erase(unique(values.begin(),values.end()),values.end());}
    int id(const T& x) const {return lower_bound(values.begin(),values.end(),x)-values.begin();}
    T value(int i) const {return values[i];}
};
