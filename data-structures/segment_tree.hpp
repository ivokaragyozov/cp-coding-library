#include <functional>
#include <vector>

using namespace std;

template <typename T, typename Merge = function<T(const T&, const T&)>,
          typename Identity = function<T()>>
class SegmentTree {
  public:
    SegmentTree(int n, Merge merge, Identity id)
        : SegmentTree(vector<T>(n, id()), merge, id) {}
    SegmentTree(const vector<T>& v, Merge merge, Identity id)
        : n((int)v.size()), data(4 * n), merge(std::move(merge)),
          id(std::move(id)) {
        build(0, 0, n - 1, v);
    }

    void set(int i, T val) { set(0, 0, n - 1, i, val); }

    T query(int l, int r) const { return query(0, 0, n - 1, l, r); }

  private:
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

    void set(int node, int l, int r, int i, T val) {
        if (l > i || r < i) {
            return;
        } else if (l == i && r == i) {
            data[node] = val;
            return;
        }

        int m = (l + r) / 2;
        set(2 * node + 1, l, m, i, val);
        set(2 * node + 2, m + 1, r, i, val);

        data[node] = merge(data[2 * node + 1], data[2 * node + 2]);
    }

    T query(int node, int l, int r, int ql, int qr) const {
        if (l > qr || r < ql) {
            return id();
        } else if (l >= ql && r <= qr) {
            return data[node];
        }

        int m = (l + r) / 2;
        return merge(query(2 * node + 1, l, m, ql, qr),
                     query(2 * node + 2, m + 1, r, ql, qr));
    }

    int n;
    vector<T> data;
    Merge merge;
    Identity id;
};
