#pragma once

#include <bits/stdc++.h>

using namespace std;

template <class T, class F> class LazySegmentTree {
    static_assert(is_convertible_v<decltype(T::merge), function<T(T, T)>>,
                  "T::merge must work as T(T, T)");
    static_assert(is_convertible_v<decltype(T::id), function<T()>>,
                  "T::id must work as T()");
    static_assert(is_convertible_v<decltype(F::apply), function<T(F, T)>>,
                  "F::apply must work as T(F, T)");
    static_assert(is_convertible_v<decltype(F::merge), function<F(F, F)>>,
                  "F::merge must work as F(F, F)");
    static_assert(is_convertible_v<decltype(F::id), function<F()>>,
                  "F::id must work as F()");

  public:
    LazySegmentTree() : LazySegmentTree(0) {}
    LazySegmentTree(int n) : LazySegmentTree(vector<T>(n, T::id())) {}
    LazySegmentTree(const vector<T> &v)
        : n((int)v.size()), data(4 * n, T::id()), lazy(4 * n, F::id()) {
        build(0, 0, n - 1, v);
    }

    void set(int i, T x) { set(0, 0, n - 1, i, x); }

    void apply(int i, F f) { apply(0, 0, n - 1, i, i, f); }

    void apply(int l, int r, F f) { apply(0, 0, n - 1, l, r, f); }

    T query(int l, int r) { return query(0, 0, n - 1, l, r); }

  private:
    void push(int node, int l, int r) {
        data[node] = F::apply(lazy[node], data[node]);

        if (l != r) {
            lazy[2 * node + 1] = F::merge(lazy[2 * node + 1], lazy[node]);
            lazy[2 * node + 2] = F::merge(lazy[2 * node + 2], lazy[node]);
        }

        lazy[node] = F::id();
    }

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

    void set(int node, int l, int r, int i, T x) {
        push(node, l, r);
        if (l > i || r < i) {
            return;
        } else if (l == r) {
            data[node] = x;
            return;
        }

        int m = (l + r) / 2;
        set(2 * node + 1, l, m, i, x);
        set(2 * node + 2, m + 1, r, i, x);

        data[node] = T::merge(data[2 * node + 1], data[2 * node + 2]);
    }

    void apply(int node, int l, int r, int ql, int qr, F f) {
        push(node, l, r);
        if (l > qr || r < ql) {
            return;
        } else if (l >= ql && r <= qr) {
            data[node] = F::apply(f, data[node]);

            if (l != r) {
                lazy[2 * node + 1] = F::merge(lazy[2 * node + 1], f);
                lazy[2 * node + 2] = F::merge(lazy[2 * node + 2], f);
            }

            return;
        }

        int m = (l + r) / 2;
        apply(2 * node + 1, l, m, ql, qr, f);
        apply(2 * node + 2, m + 1, r, ql, qr, f);

        data[node] = T::merge(data[2 * node + 1], data[2 * node + 2]);
    }

    T query(int node, int l, int r, int ql, int qr) {
        push(node, l, r);

        if (l > qr || r < ql) {
            return T::id();
        } else if (l >= ql && r <= qr) {
            return data[node];
        }

        int m = (l + r) / 2;

        auto res = T::merge(query(2 * node + 1, l, m, ql, qr),
                            query(2 * node + 2, m + 1, r, ql, qr));

        data[node] = T::merge(data[2 * node + 1], data[2 * node + 2]);
        return res;
    }

    int n;
    vector<T> data;
    vector<F> lazy;
};
