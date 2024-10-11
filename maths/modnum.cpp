#include <cstdint>
#include <istream>
#include <ostream>

template <int MOD> struct ModNum {
    int v;

    ModNum() : v(0) {}
    ModNum(int _v) : v(_v % MOD) {}
    ModNum(int64_t _v) : v(_v % MOD) {}

    operator int() const { return v; }

    friend std::ostream &operator<<(std::ostream &o, ModNum &x) {
        return o << (int)x;
    }
    friend std::istream &operator>>(std::istream &i, ModNum &x) {
        int64_t val;
        i >> val;

        x = ModNum(val);
        return i;
    }

    friend ModNum fastPow(const ModNum &x, int pw) {
        if (pw == 0) {
            return ModNum(1);
        } else if (pw % 2 == 0) {
            ModNum aux = fastPow(x, pw / 2);
            return aux * aux;
        } else {
            ModNum aux = fastPow(x, pw - 1);
            return aux * x;
        }
    }

    ModNum inv() const { return fastPow(*this, MOD - 2); }

    ModNum &operator++() {
        v++;
        if (v == MOD) {
            v = 0;
        }
        return *this;
    }
    ModNum operator++(int) {
        ModNum aux(*this);
        (*this)++;
        return aux;
    }

    ModNum &operator--() {
        v--;
        if (v == -1) {
            v = MOD - 1;
        }
        return *this;
    }
    ModNum &operator--(int) {
        ModNum aux(*this);
        (*this)--;
        return aux;
    }

    ModNum &operator+=(const ModNum &o) {
        v += o.v;

        if (v >= MOD) {
            v -= MOD;
        }

        return *this;
    }
    ModNum &operator-=(const ModNum &o) {
        v -= o.v;

        if (v < 0) {
            v += MOD;
        } else if (v >= MOD) {
            v -= MOD;
        }

        return *this;
    }
    ModNum &operator*=(const ModNum &o) {
        v = ((int64_t)v * o.v) % MOD;
        return *this;
    }
    ModNum &operator/=(const ModNum &o) { return *this *= o.inv(); }

    friend ModNum operator+(const ModNum &a, const ModNum &b) {
        return ModNum(a) += b;
    }
    friend ModNum operator-(const ModNum &a, const ModNum &b) {
        return ModNum(a) -= b;
    }
    friend ModNum operator*(const ModNum &a, const ModNum &b) {
        return ModNum(a) *= b;
    }
    friend ModNum operator/(const ModNum &a, const ModNum &b) {
        return ModNum(a) /= b;
    }

    friend ModNum operator+(const ModNum &a, int b) { return a + ModNum(b); }
    friend ModNum operator-(const ModNum &a, int b) { return a - ModNum(b); }
    friend ModNum operator*(const ModNum &a, int b) { return a * ModNum(b); }
    friend ModNum operator/(const ModNum &a, int b) { return a / ModNum(b); }

    friend ModNum operator+(int a, const ModNum &b) { return ModNum(a) + b; }
    friend ModNum operator-(int a, const ModNum &b) { return ModNum(a) - b; }
    friend ModNum operator*(int a, const ModNum &b) { return ModNum(a) * b; }
    friend ModNum operator/(int a, const ModNum &b) { return ModNum(a) / b; }

    friend ModNum operator+(const ModNum &a, int64_t b) {
        return a + ModNum(b);
    }
    friend ModNum operator-(const ModNum &a, int64_t b) {
        return a - ModNum(b);
    }
    friend ModNum operator*(const ModNum &a, int64_t b) {
        return a * ModNum(b);
    }
    friend ModNum operator/(const ModNum &a, int64_t b) {
        return a / ModNum(b);
    }

    friend ModNum operator+(int64_t a, const ModNum &b) {
        return ModNum(a) + b;
    }
    friend ModNum operator-(int64_t a, const ModNum &b) {
        return ModNum(a) - b;
    }
    friend ModNum operator*(int64_t a, const ModNum &b) {
        return ModNum(a) * b;
    }
    friend ModNum operator/(int64_t a, const ModNum &b) {
        return ModNum(a) / b;
    }
};
