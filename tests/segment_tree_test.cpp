#include <iostream>
#include <vector>

#include "data_structures/segment_tree.hpp"

using SumSegTree =
    SegmentTree<int64_t, [](auto a, auto b) { return a + b; }, []() -> int64_t { return 0; }>;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    std::cin >> n >> q;

    std::vector<int64_t> a(n);
    for (auto& x : a) {
        std::cin >> x;
    }

    SumSegTree segTree = SumSegTree(a);
    while (q--) {
        int type;
        std::cin >> type;

        if (type == 0) {
            int p, x;
            std::cin >> p >> x;

            segTree.set(p, segTree.query(p, p) + x);
        }
        else {
            int l, r;
            std::cin >> l >> r;

            std::cout << segTree.query(l, r - 1) << std::endl;
        }
    }
}
