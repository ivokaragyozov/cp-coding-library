template <typename T> struct FenwickTree {
    int treeSize;
    vector<T> data;

    FenwickTree(int _size) : treeSize(_size), data(_size + 1, 0) {}

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

    T getInterval(int low, int high) { return get(high) - get(low - 1); }
};
