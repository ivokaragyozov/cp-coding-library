#pragma once

#include <bits/stdc++.h>

using namespace std;

template <class T> class SegmentTree {
    static_assert(is_convertible_v<decltype(T::merge), function<T(T, T)>>,
                  "T::merge must work as T(T, T)");
    static_assert(is_convertible_v<decltype(T::id), function<T()>>,
                  "T::id must work as T()");

  public:
    SegmentTree() : SegmentTree(0) {}
    SegmentTree(int n) : SegmentTree(vector<T>(n, T::id())) {}
    SegmentTree(const vector<T> &v) : n((int)v.size()), data(4 * n) {
        build(0, 0, n - 1, v);
    }

    void set(int i, T val) { set(0, 0, n - 1, i, val); }

    T query(int l, int r) const { return query(0, 0, n - 1, l, r); }

    template <class F> int max_right(int l, F f) const {
        static_assert(is_convertible_v<decltype(f), function<bool(T)>>,
                      "f must work as bool(T)");
        return max_right(0, 0, n - 1, l, f);
    }

    template <class F> int min_left(int r, F f) const {
        static_assert(is_convertible_v<decltype(f), function<bool(T)>>,
                      "f must work as bool(T)");
        return min_left(0, 0, n - 1, r, f);
    }

  private:
    void build(int node, int l, int r, const vector<T> &v) {
        if (l == r) {
            data[node] = v[l];
            return;
        }

        int m = (l + r) / 2;
        build(2 * node + 1, l, m, v);
        build(2 * node + 2, m + 1, r, v);

        data[node] = T::merge(data[2 * node + 1], data[2 * node + 2]);
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

        data[node] = T::merge(data[2 * node + 1], data[2 * node + 2]);
    }

    T query(int node, int l, int r, int ql, int qr) const {
        if (l > qr || r < ql) {
            return T::id();
        } else if (l >= ql && r <= qr) {
            return data[node];
        }

        int m = (l + r) / 2;
        return T::merge(query(2 * node + 1, l, m, ql, qr),
                        query(2 * node + 2, m + 1, r, ql, qr));
    }

    template <class F>
    int max_right(int node, int l, int r, int ql, F f, T acc = T::id()) const {
        if (r < ql) {
            return -1;
        } else if (l >= ql && f(T::merge(acc, data[node]))) {
            acc = T::merge(acc, data[node]);
            return -1;
        } else if (l == r) {
            return r;
        }

        int m = (l + r) / 2;
        int left = max_right(2 * node + 1, l, m, ql, f, acc);
        if (left != -1) {
            return left;
        }

        return max_right(2 * node + 2, m + 1, r, ql, f, acc);
    }

    template <class F>
    int min_left(int node, int l, int r, int qr, F f, T acc = T::id()) const {
        if (l > qr) {
            return -1;
        } else if (r <= qr && f(T::merge(data[node], acc))) {
            acc = T::merge(data[node], acc);
            return -1;
        } else if (l == r) {
            return l;
        }

        int m = (l + r) / 2;
        int right = min_left(2 * node + 2, m + 1, r, qr, f, acc);
        if (right != -1) {
            return right;
        }

        return min_left(2 * node + 1, l, m, qr, f, acc);
    }

    int n;
    vector<T> data;
};
