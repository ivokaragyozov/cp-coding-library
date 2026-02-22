#pragma once

#include <bit>
#include <vector>

// op and e must form a monoid over S:
//   - associativity: op(op(a, b), c) == op(a, op(b, c))
//   - identity:      op(e(), x) == op(x, e()) == x
template <class S, auto op, auto e>
class SegmentTree {
    static_assert(std::is_invocable_r_v<S, decltype(op), S, S>, "op must be callable as S(S, S)");
    static_assert(std::is_invocable_r_v<S, decltype(e)>, "e must be callable as S()");

public:
    explicit SegmentTree(int n) : SegmentTree(std::vector<S>(n, e())) {
    }

    explicit SegmentTree(const std::vector<S>& v)
        : n(static_cast<int>(v.size())),
          sz(std::bit_ceil(static_cast<unsigned>(n))),
          data(2 * sz, e()) {
        for (int i = 0; i < n; i++) {
            data[sz + i] = v[i];
        }
        for (int i = sz - 1; i >= 1; i--) {
            data[i] = op(data[2 * i], data[2 * i + 1]);
        }
    }

    void set(int i, S val) {
        data[i += sz] = val;
        for (i >>= 1; i >= 1; i >>= 1) {
            data[i] = op(data[2 * i], data[2 * i + 1]);
        }
    }

    [[nodiscard]] S query(int l, int r) const {
        S res_l = e(), res_r = e();
        for (l += sz, r += sz + 1; l < r; l >>= 1, r >>= 1) {
            if (l & 1) {
                res_l = op(res_l, data[l++]);
            }
            if (r & 1) {
                res_r = op(data[--r], res_r);
            }
        }
        return op(res_l, res_r);
    }

private:
    int n, sz;
    std::vector<S> data;
};
