// WHEN: randomized fingerprints for set-like data. TIME: O(1) per key. ASSUMES: collisions remain possible; not cryptographic.
// Randomized XOR fingerprints for sets/multisets of small integer keys.
// Collision probability is small, never zero; do not use as a cryptographic hash.
uint64_t splitmix64(uint64_t x) {
    x+=0x9e3779b97f4a7c15ULL; x=(x^(x>>30))*0xbf58476d1ce4e5b9ULL;
    x=(x^(x>>27))*0x94d049bb133111ebULL; return x^(x>>31);
}
struct XorHash {
    uint64_t seed = chrono::steady_clock::now()
        .time_since_epoch()
        .count();
    uint64_t operator()(uint64_t x) const { return splitmix64(x+seed); }
};
// Set fingerprint: XOR hash(x) for every element; add/remove toggles the same value.
// For multisets, XOR loses even multiplicities; use a sum of random hashes instead.
