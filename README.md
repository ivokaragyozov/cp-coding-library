# Competitive Programming Library

A personal C++ library for competitive programming, featuring common data structures and algorithms.

## Structure

```
.
├── data-structures/
│   ├── segment_tree.hpp      # Segment tree with custom merge
│   ├── lazy_segment_tree.hpp # Lazy propagation segment tree
│   ├── fenwick_tree.hpp      # Fenwick tree (BIT)
│   ├── treap.hpp             # Treap (BST)
│   └── implicit_treap.hpp    # Implicit treap with reversals
├── graphs/
│   ├── scc.hpp               # Strongly connected components (Kosaraju)
│   └── max_flow.hpp          # Maximum flow (Dinic)
├── strings/
│   ├── suffix_array.hpp      # Suffix array with LCP
│   └── hash.hpp              # Polynomial hashing (Rabin-Karp)
├── maths/
│   └── modnum.hpp            # Modular arithmetic
├── template.cpp              # Contest template
└── expander.py               # Include expander for submissions
```

## Usage

Include headers in your solution:

```cpp
#include "data-structures/segment_tree.hpp"
```

### Expander

The `expander.py` tool (inspired by [AtCoder Library](https://github.com/atcoder/ac-library)) combines your source file with all included library headers into a single `combined.cpp` for submission.

```bash
python expander.py solution.cpp
```

Options:
- `-c, --console` - Print to stdout instead of writing to `combined.cpp`
- `--lib PATH` - Specify library path
- `--origname NAME` - Preserve original line numbers in error messages

The expander also respects the `CPLUS_INCLUDE_PATH` environment variable.

## Data Structures

### Segment Tree

```cpp
auto merge = [](int a, int b) { return a + b; };
auto id = []() { return 0; };

SegmentTree<int, decltype(merge), decltype(id)> st(n, merge, id);
st.set(i, val);
int sum = st.query(l, r);
```

### Lazy Segment Tree

```cpp
LazySegmentTree<T, F, ...> st(n, merge, id, lazy_apply, lazy_merge, lazy_id);
st.apply(l, r, f);
T result = st.query(l, r);
```

### Fenwick Tree

```cpp
Fenwick<long long> fw(n);
fw.update(i, delta);        // 1-indexed
long long prefix = fw.get(i);
long long range = fw.get_interval(l, r);
```

### Treap

```cpp
Treap<int> treap;
treap.insert_val(x);
treap.delete_single(x);
int kth = treap.find_kth(k);
int order = treap.find_order(x);
```

### Implicit Treap

```cpp
ImplicitTreap<int> treap;
treap.insertAtInd(ind, treap.getNode(val));
treap.reverseInterval(l, r);
```

## Graphs

### Strongly Connected Components

```cpp
vector<pair<int, int>> edges = {{0, 1}, {1, 2}, {2, 0}};
SCC scc(n, edges);
int component = scc.g[v].comp;
// scc.dag contains the condensation graph
```

### Maximum Flow (Dinic)

```cpp
MaxFlow<long long> flow(n);
flow.add_edge(u, v, capacity);
long long max_flow = flow.get_max_flow(source, sink);
```

## Strings

### Suffix Array

```cpp
SuffixArray sa("banana");
bool found = sa.contains("nan");
int count = sa.count_occurances("ana");
long long distinct = sa.count_different_substrings();
```

### Polynomial Hashing

```cpp
Hash<31> h;
h.init(max_len);
auto hashes = h.rabin_karp(s);
auto hash_lr = h.get_range(hashes, l, r);
```

## Math

### Modular Arithmetic

```cpp
const int MOD = 1e9 + 7;
using mint = ModNum<MOD>;

mint a = 5, b = 3;
mint c = a * b + a / b;
mint inv = a.inv();
mint pw = fast_pow(a, 1000000);
```
