#include <functional>
#include <vector>

using namespace std;

template <class T, auto merge, auto identity> class SegmentTree {
    static_assert(is_convertible_v<decltype(merge), function<T(T, T)>>,
                  "merge must work as T(T, T)");
    static_assert(is_convertible_v<decltype(identity), function<T()>>,
                  "identity must work as T()");

  public:
    SegmentTree() : SegmentTree(0) {}
    SegmentTree(int n) : SegmentTree(vector<T>(n, identity())) {}
    SegmentTree(const vector<T> &v) : n((int)v.size()) {
        data.resize(4 * n);
        build(1, 1, n, v);
    }

    void set(int i, T val) { set(1, 1, n, i, val); }

    T query(int l, int r) const { return query(1, 1, n, l, r); }

    template <class F> int max_right(int l, F f) const {
        return max_right(1, 1, n, l, f);
    }

  private:
    void build(int node, int l, int r, const vector<T> &v) {
        if (l == r) {
            data[node] = v[l - 1];
            return;
        }

        int m = (l + r) / 2;
        build(2 * node, l, m, v);
        build(2 * node + 1, m + 1, r, v);

        data[node] = merge(data[2 * node], data[2 * node + 1]);
    }

    void set(int node, int l, int r, int i, T val) {
        if (l > i || r < i) {
            return;
        } else if (l == i && r == i) {
            data[node] = val;
            return;
        }

        int m = (l + r) / 2;
        set(2 * node, l, m, i, val);
        set(2 * node + 1, m + 1, r, i, val);

        data[node] = merge(data[2 * node], data[2 * node + 1]);
    }

    T query(int node, int l, int r, int ql, int qr) const {
        if (l > qr || r < ql) {
            return identity();
        } else if (l >= ql && r <= qr) {
            return data[node];
        }

        int m = (l + r) / 2;
        return merge(query(2 * node, l, m, ql, qr),
                     query(2 * node + 1, m + 1, r, ql, qr));
    }

    template <class F>
    int max_right(int node, int l, int r, int ql, F f,
                  T acc = identity()) const {
        if (r < ql) {
            return -1;
        } else if (l >= ql && f(merge(acc, data[node]))) {
            acc = merge(acc, data[node]);
            return -1;
        } else if (l == r) {
            return l;
        }

        int m = (l + r) / 2;
        int left = max_right(2 * node, l, m, ql, f, acc);
        if (left != -1) {
            return left;
        }

        return max_right(2 * node + 1, m + 1, r, ql, f, acc);
    }

    int n;
    vector<T> data;
};
