# KUET Phantoms — ICPC Team Notebook

A comprehensive algorithm and data structure reference notebook for competitive programming contests, particularly designed for **ICPC (International Collegiate Programming Contest)**.

---

## 👥 Team Members

**Team:** `KUET_Phantoms`  
**University:** Khulna University of Engineering and Technology (KUET)

| Name |
|------|
| Sakiful Siam |
| Nihan Mahmud |
| Mohammad Adib Chowdhury |

---

## 📚 Contents

This notebook includes implementations and reference materials for:

| Category | Topics |
|----------|--------|
| **Data Structures** | Fenwick Tree, 2D Fenwick Tree, Fast BIT & Iterative SegTree, Lazy Segment Tree, Dynamic Segment Tree, Persistent Segment Tree, Segment Tree, Treap (Implicit), Monotonic Stack & Queue, DSU, DSU with Rollback, Wavelet Tree, Li Chao Tree, MO's Algorithm, MO with Updates, Sqrt Decomposition, Sqrt Tricks, Static Range Queries, Coordinate Compression, Binary Trie (max XOR) |
| **Dynamic Programming** | DP Fundamentals, Bitmask DP, Digit DP, Divide & Conquer DP, CHT DP, SOS DP, Expected Value DP, Knapsack & Common DP Patterns (Tree Knapsack, Bounded Knapsack, Bitset Subset-Sum, Edit Distance), LIS & LCS, Knuth Optimization, Matrix Exponentiation, DP with Fenwick Tree |
| **Flow** | Dinic's Max Flow, Min-Cost Max-Flow, Hopcroft-Karp, Kuhn, Hungarian Algorithm, Flow Applications & Reductions (Min Cut, Project Selection, König, Dilworth) |
| **Game Theory** | Nim Theory & Notes, Sprague-Grundy Theorem (Mex, Subtraction Game, DAG Games) |
| **Geometry** | Basic Geometry (Shared Point struct), Convex Hull, Rotating Calipers, Closest Pair of Points, Point in Polygon, Line/Circle Intersection, Half-Plane Intersection |
| **Graph** | Graph Basics (BFS/DFS, Dijkstra, 0-1 BFS, Topological Sort, Kruskal, Multi-source BFS), Bellman-Ford, Floyd-Warshall, Articulation Points & Bridges, Biconnected Components, SCC, 2-SAT, Eulerian Path & Circuit, Centroid Decomposition (with worked example), Heavy Light Decomposition, DSU on Tree (with worked example), Mo on Tree (with worked example), Tree DP, Tree Queries |
| **Math** | Sieve (SPF, Linear Sieve, Segmented Sieve), NTT (Polynomial Multiply mod 998244353), Gaussian Elimination (Double & Mod p), Floor Sum & BSGS, Primitive Root, Miller-Rabin & Pollard-Rho, Modular Inverse, CRT, Linear Diophantine Equation, Euler Phi & Mobius, Euler Theorem & Power Towers, Lucas Theorem, Sum of Divisors, Exact GCD Counting, Stirling Numbers, Combinatorics & Probability |
| **Misc** | Template (Fast IO, Debug Macro, Compile Flags, pb_ds Ordered Set, Custom Hash, __int128 IO, Stress-test script), Contest Checklist & Complexity Table, STL Reference, Bit Hacks, XOR Hashing |
| **Searching** | Basic Binary Search, Basic Array Patterns, Range & Search Techniques |
| **String** | KMP, Z-Algorithm, Manacher, Aho-Corasick, Suffix Array, Suffix Automaton, Palindromic Tree (Eertree), Lyndon Factorization & Min Rotation, Mersenne 61-bit Hash, Rolling Hash (Randomized Base), Trie |

---

## ⚙️ Prerequisites

### Required Software

- **[Python 2/3](https://www.python.org/)** — For PDF generation script
- **[latexmk](https://www.ctan.org/pkg/latexmk/)** — For automated LaTeX compilation

---

## 🏗️ Generating the Notebook

> This Python script is a fork of the **Stanford ICPC Team's** notebook generator. The included script differs from the original — here, **directories become sections** and the **filename (without extension) becomes the subsection**. Code comments also support **LaTeX math formatting**.

### Generate PDF

Run the build script:

```bash
python generate_pdf.py
```

- The LaTeX template used by the script is `notebook.tex`
- It recognizes common file extensions for **C, C++, Java, and Python** and applies syntax highlighting automatically

### Customization

To change the **color scheme** or **add support for additional languages**, both `notebook.tex` and `generate_pdf.py` should be modified accordingly.

---

## 📁 Project Structure

```
.
├── code/                        # Algorithm implementations
│   ├── Data Structure/
│   ├── Dynamic Programming/
│   ├── Flow/
│   ├── Game Theory/
│   ├── Geometry/
│   ├── Graph/
│   ├── Math/
│   ├── Misc/
│   ├── Searching/
│   └── String/
├── math/                        # Mathematical formulas and references (LaTeX)
├── notebook.tex                 # Main LaTeX document
├── contents.tex                 # Auto-generated content file
├── notebook.pdf                 # Compiled notebook (output)
├── generate_pdf.py              # PDF generation script
└── README.md                    # This file
```

---

## ➕ Adding New Algorithms

To add a new algorithm to the notebook:

1. **Add your code file** to the appropriate directory under `code/`:

   ```bash
   # Example: Adding a new graph algorithm
   code/Graph/MyNewAlgorithm.cpp
   ```

2. **Follow naming conventions:**
   - Use descriptive filenames
   - Supported extensions: `.cpp`, `.cc`, `.java`, `.py`, `.txt`

3. **Rebuild the PDF:**

   ```bash
   python3 generate_pdf.py
   ```

The script will automatically detect and include the new file in the generated PDF.

---

## 🎨 Customization

| What to change | Where |
|---|---|
| Font sizes | `\fontsize` commands in `notebook.tex` |
| Page layout | `geometry` settings in the preamble of `notebook.tex` |
| Syntax highlighting | `minted` settings in `notebook.tex` |
| Section ordering | `generate_pdf.py` |

### Code Formatting

The notebook uses the `minted` package for syntax highlighting with:
- Line numbers
- Automatic line breaking
- Compact formatting optimized for printing

---

## 🏆 Tips for Contest Use

- Print the PDF before the contest (if allowed by rules)
- Test compilation before the contest day
- Verify all algorithms are working correctly
- Know where to find specific algorithms in the notebook
- Practice using the notebook during practice sessions

---

## 🐛 Common Issues

| Issue | Solution |
|---|---|
| `minted` Error | Ensure Pygments is installed and use `-shell-escape` flag |
| Font Errors | Install the complete TeXLive distribution |
| Missing Packages | Run `sudo tlmgr install minted fvextra catchfile xstring framed` |
| Python Script Fails | Check Python version (3.x required) and file permissions |

---

## 📄 Output

The final `notebook.pdf` includes:
- Table of contents with page numbers
- Syntax-highlighted code listings
- Mathematical formulas and theorems
- Optimized for printing in landscape format
- Compact multi-column layout

---

*Last Updated: October 2026*  
*Compiled for: ICPC and other competitive programming contests*
