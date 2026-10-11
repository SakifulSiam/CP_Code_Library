// Handy STL patterns. Include <bits/stdc++.h> and use namespace std.
vector<int> a{1,2,3,4}, b{2,4,6}, v{1,3,5};
set<int> s{1,4,7};
// nth_element: puts the element that would be at k in sorted order at position k.
// Average O(n); elements on either side are not fully sorted.
// nth_element(a.begin(), a.begin()+k, a.end()); // k-th smallest, 0-indexed

// Iterator helpers: distance(first,last), advance(it,k), next(it), prev(it).
// For vector iterators these are O(1); for set/map iterators they are O(n).
auto it = lower_bound(v.begin(), v.end(), x); // sorted vector: first value >= x
auto jt = next(s.begin());                   // ordered containers: move by one

// Set algorithms require sorted ranges and write into an output iterator.
vector<int> out;
set_intersection(a.begin(),a.end(),b.begin(),b.end(),back_inserter(out));
// Also: set_union, set_difference, set_symmetric_difference.

// bitset: fixed compile-time number of bits, useful for compact state sets.
bitset<1000> mask; mask.set(3); mask.flip(5); bool has = mask.test(3);

// tuple: group values of different types. Structured binding since C++17.
tuple<int,string,long long> item={1,"name",42};
auto [id,name,value]=item;

// transform: apply a function elementwise. partition: split by a predicate.
vector<int> squares(a.size());
transform(a.begin(),a.end(),squares.begin(),[](int x){return x*x;});
auto middle=partition(a.begin(),a.end(),[](int x){return x%2==0;});
