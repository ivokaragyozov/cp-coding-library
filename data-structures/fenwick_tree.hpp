/* -------------------------- Fenwick -------------------------- */
#pragma once
#include <bits/stdc++.h>

using namespace std;

template <typename T> class Fenwick {
  public:
    Fenwick(int _size) : treeSize(_size), data(_size + 1, 0) {}

    void update(int ind, T val) {
        while (ind <= treeSize) {
            data[ind] += val;
            ind += (ind & (-ind));
        }
    }

    T get(int ind) {
        T ans{};
        while (ind > 0) {
            ans += data[ind];
            ind -= (ind & (-ind));
        }
        return ans;
    }

    T get_interval(int low, int high) { return get(high) - get(low - 1); }

  private:
    int treeSize;
    vector<T> data;
};
/* -------------------------- Fenwick -------------------------- */
