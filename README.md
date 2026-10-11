# KUET Phantoms Code Library

The notebook PDF identifies the team as KUET Phantoms and lists Sakiful Siam, Nihan Mahmud, and Mohammad Adib Chowdhury.

This library is a competitive programming reference. The C++ files are usually snippets rather than standalone programs; include the required headers and adapt indexing, limits, and operation types to the problem.

## Build

Run python generate_pdf.py to regenerate contents.tex and notebook.pdf. The script copies snippets into _tmp_code/ for LaTeX minted. The PDF uses the metadata in notebook.tex.

## Notes for advanced templates

| Template | When to use | Complexity | Assumptions |
|---|---|---|---|
| DSU with rollback | Undo unions in offline divide-and-conquer or time-segment traversal | Find/unite O(log n); rollback proportional to changes | No path compression; snapshot is history size |
| Mo with updates | Offline range queries mixed with point assignments | About O((N+Q)N^(2/3)) moves | 0-indexed inclusive ranges; updates include before/after values and query time |
| Dynamic segment tree | Sparse range operations on a huge coordinate domain | O(log C) per operation | Fixed [0, 1e9] domain; range add and sum |
| Persistent segment tree | Historical versions, range kth order statistics | O(log n) per inserted value/query | Nonempty input; prefix roots; compressed values |
| Wavelet tree | Static range kth order statistic | O(log sigma) per query | Static array and declared value domain |
| HLD | Path sums with point assignments | O(log^2 n) per path query | One connected tree; 0-indexed vertices |
| DSU on tree | Per-subtree frequency/statistic queries | O(n log n) with small-to-large traversal | User supplies add/remove and answer callbacks |
| Mo on tree | Offline path queries with a toggleable vertex statistic | Typically O((n+q)sqrt(n)) toggles | Static tree; supply LCA and toggle callbacks |
| Centroid decomposition | Distance queries/updates over a tree | O(n log n) build | Tree input; callback handles each centroid |
| Knuth optimization | Certain interval DP recurrences | O(n^2) | Must prove the quadrangle inequality and monotone-opt condition |
| SOS/Zeta transform | Aggregate values over all submasks/supermasks | O(k 2^k) | Small bit count k |
| Monotone CHT DP | DP line queries with ordered slopes and x values | O(1) amortized per add/query | Slopes decrease; query x values increase |
| Li Chao tree (dynamic CHT) | Add arbitrary lines and query minimum | O(log C) per operation | Integer x in [-1e9,1e9]; arithmetic must not overflow |

The math appendix in PDF section 10 contains the longer combinatorics and number-theory formula sheet; the Combinatorics and Probability source file focuses on code and brief reminders.

The personal notebook also includes beginner references for binary search, prefix sums, difference arrays, two pointers, sliding windows, common arithmetic sums, and modular arithmetic. Selected graph, matching, number-theory, and geometry references are included as separate snippets; advanced geometry notes describe assumptions and the main algorithm rather than claiming to be a drop-in implementation.
