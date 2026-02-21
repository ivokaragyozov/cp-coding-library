#include <functional>
#include <vector>

using namespace std;

template <typename T, typename F, typename Merge = function<T(const T&, const T&)>,
          typename Identity = function<T()>, typename LazyApply = function<T(const F&, const T&)>,
          typename LazyMerge = function<F(const F&, const F&)>,
          typename LazyIdentity = function<F()>>
class LazySegmentTree {
public:
    LazySegmentTree() : LazySegmentTree(0) {
    }

    LazySegmentTree(int n, Merge merge, Identity id, LazyApply lazy_apply, LazyMerge lazy_merge,
                    function<F()> lazy_id)
        : LazySegmentTree(vector<T>(n, id()), merge, id, lazy_apply, lazy_merge, lazy_id) {
    }

    LazySegmentTree(const vector<T>& v, Merge merge, Identity id, LazyApply lazy_apply,
                    LazyMerge lazy_merge, LazyIdentity lazy_id)
        : n(static_cast<int>(v.size())),
          data(v),
          lazy(4 * n, lazy_id()),
          merge(move(merge)),
          id(move(id)),
          lazy_apply(move(lazy_apply)),
          lazy_merge(move(lazy_merge)),
          lazy_id(move(lazy_id)) {
        build(0, 0, n - 1, v);
    }

    void set(int i, T x) {
        set(0, 0, n - 1, i, x);
    }

    void apply(int i, F f) {
        apply(0, 0, n - 1, i, i, f);
    }

    void apply(int l, int r, F f) {
        apply(0, 0, n - 1, l, r, f);
    }

    T query(int l, int r) {
        return query(0, 0, n - 1, l, r);
    }

private:
    void push(int node, int l, int r) {
        data[node] = lazy_apply(lazy[node], data[node]);

        if (l != r) {
            lazy[2 * node + 1] = lazy_merge(lazy[2 * node + 1], lazy[node]);
            lazy[2 * node + 2] = lazy_merge(lazy[2 * node + 2], lazy[node]);
        }

        lazy[node] = lazy_id();
    }

    void build(int node, int l, int r, const vector<T>& v) {
        if (l == r) {
            data[node] = v[l];
            return;
        }

        int m = (l + r) / 2;
        build(2 * node + 1, l, m, v);
        build(2 * node + 2, m + 1, r, v);

        data[node] = merge(data[2 * node + 1], data[2 * node + 2]);
    }

    void set(int node, int l, int r, int i, T x) {
        push(node, l, r);
        if (l > i || r < i) {
            return;
        }
        else if (l == r) {
            data[node] = x;
            return;
        }

        int m = (l + r) / 2;
        set(2 * node + 1, l, m, i, x);
        set(2 * node + 2, m + 1, r, i, x);

        data[node] = merge(data[2 * node + 1], data[2 * node + 2]);
    }

    void apply(int node, int l, int r, int ql, int qr, F f) {
        push(node, l, r);
        if (l > qr || r < ql) {
            return;
        }
        else if (l >= ql && r <= qr) {
            data[node] = lazy_apply(f, data[node]);

            if (l != r) {
                lazy[2 * node + 1] = lazy_merge(lazy[2 * node + 1], f);
                lazy[2 * node + 2] = lazy_merge(lazy[2 * node + 2], f);
            }

            return;
        }

        int m = (l + r) / 2;
        apply(2 * node + 1, l, m, ql, qr, f);
        apply(2 * node + 2, m + 1, r, ql, qr, f);

        data[node] = merge(data[2 * node + 1], data[2 * node + 2]);
    }

    T query(int node, int l, int r, int ql, int qr) {
        push(node, l, r);

        if (l > qr || r < ql) {
            return id();
        }
        else if (l >= ql && r <= qr) {
            return data[node];
        }

        int m = (l + r) / 2;
        data[node] =
            merge(query(2 * node + 1, l, m, ql, qr), query(2 * node + 2, m + 1, r, ql, qr));

        return data[node];
    }

    Merge merge;
    Identity id;
    LazyApply lazy_apply;
    LazyMerge lazy_merge;
    LazyIdentity lazy_id;

    int n;
    vector<T> data;
    vector<F> lazy;
};
