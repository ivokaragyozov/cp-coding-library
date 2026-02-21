#include <iostream>
#include <vector>

#include "data_structures/segment_tree.hpp"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    std::cin >> n >> q;

    std::vector<int64_t> a(n);
    for (auto& x : a) {
        std::cin >> x;
    }

    SegmentTree<int64_t, [](auto a, auto b) { return a + b; }, []() { return 0; }> segTree(a);
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

        for (int i = 0; i < n; i++) {
            std::cout << segTree.query(i, i) << " ";
        }
        std::cout << std::endl;
    }
}
