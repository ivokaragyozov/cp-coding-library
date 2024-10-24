/* -------------------------- SegmentTree -------------------------- */
#pragma once
#include <bits/stdc++.h>

using namespace std;

template <typename T> class SegmentTree {
  private:
    int treeSize;
    vector<T> data, lazy;

    void push_lazy(int node, int low, int high) {
        data[node] += (high - low + 1) * lazy[node];

        if (low != high) {
            lazy[(node << 1)] += lazy[node];
            lazy[(node << 1) + 1] += lazy[node];
        }

        lazy[node] = 0;
    }

    void update(int node, int low, int high, int qLow, int qHigh, T qVal) {
        push_lazy(node, low, high);

        if (low > qHigh || high < qLow) {
            return;
        }
        if (low >= qLow && high <= qHigh) {
            lazy[node] += qVal;
            push_lazy(node, low, high);
            return;
        }

        int mid = ((low + high) >> 1);
        update((node << 1), low, mid, qLow, qHigh, qVal);
        update((node << 1) + 1, mid + 1, high, qLow, qHigh, qVal);

        data[node] = data[(node << 1)] + data[(node << 1) + 1];
    }

    T query(int node, int low, int high, int qLow, int qHigh) {
        push_lazy(node, low, high);

        if (low > qHigh || high < qLow) {
            return 0;
        }
        if (low >= qLow && high <= qHigh) {
            return data[node];
        }

        int mid = ((low + high) >> 1);
        return query((node << 1), low, mid, qLow, qHigh) +
               query((node << 1) + 1, mid + 1, high, qLow, qHigh);
    }

  public:
    SegmentTree(int _size)
        : treeSize(_size), data(4 * _size), lazy(4 * _size) {}

    void update(int low, int high, T val) {
        update(1, 1, treeSize, low, high, val);
    }

    T query(int low, int high) { return query(1, 1, treeSize, low, high); }
};
/* -------------------------- SegmentTree -------------------------- */
