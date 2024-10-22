/* -------------------------- Hash -------------------------- */
#include <cstddef>
#include <vector>

#include "../maths/modnum.cpp"

using namespace std;

const int MOD = 1e9 + 7;
using modnum_t = ModNum<MOD>;

template <int BASE> class Hash {
  private:
    void precompute_base_pow(size_t n) {
        basePow.resize(n);

        basePow[0] = 1;
        for (int j = 1; j < n; j++) {
            basePow[j] = basePow[j - 1] * BASE;
        }
    }

  public:
    vector<modnum_t> basePow;

    void init(size_t n) { precompute_base_pow(n); }

    template <typename T> vector<modnum_t> rabin_karp(const T &container) {
        vector<modnum_t> h(container.size());
        for (size_t j = 0; j < container.size(); j++) {
            h[j] = (j ? h[j - 1] : modnum_t(0)) * BASE + container[j];
        }
        return h;
    }

    modnum_t get_range(const vector<modnum_t> &h, int l, int r) {
        return h[r] - (l ? h[l - 1] * basePow[r - l + 1] : modnum_t(0));
    }
};
/* -------------------------- Hash -------------------------- */
