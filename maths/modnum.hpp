#include <istream>
#include <ostream>

using namespace std;

using ll = long long;

template <int MOD>
class ModNum {
private:
    int v;

public:
    constexpr ModNum() : v(0) {
    }

    constexpr ModNum(int _v) : v((_v % MOD + MOD) % MOD) {
    }

    constexpr ModNum(ll _v) : v((_v % MOD + MOD) % MOD) {
    }

    operator int() const {
        return v;
    }

    friend ostream& operator<<(ostream& o, const ModNum& x) {
        return o << (int)x;
    }

    friend istream& operator>>(istream& i, ModNum& x) {
        ll val;
        i >> val;

        x = ModNum(val);
        return i;
    }

    template <typename U>
    friend ModNum fast_pow(const ModNum& x, U pw) {
        if (pw == 0) {
            return ModNum(1);
        }
        else if (pw % 2 == 0) {
            ModNum aux = fast_pow(x, pw / 2);
            return aux * aux;
        }
        else {
            ModNum aux = fast_pow(x, pw - 1);
            return aux * x;
        }
    }

    ModNum inv() const {
        return fast_pow(*this, MOD - 2);
    }

    ModNum& operator++() {
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

    ModNum& operator--() {
        v--;
        if (v == -1) {
            v = MOD - 1;
        }
        return *this;
    }

    ModNum& operator--(int) {
        ModNum aux(*this);
        (*this)--;
        return aux;
    }

    ModNum& operator+=(const ModNum& o) {
        v += o.v;

        if (v >= MOD) {
            v -= MOD;
        }

        return *this;
    }

    ModNum& operator-=(const ModNum& o) {
        v -= o.v;

        if (v < 0) {
            v += MOD;
        }
        else if (v >= MOD) {
            v -= MOD;
        }

        return *this;
    }

    ModNum& operator*=(const ModNum& o) {
        v = ((ll)v * o.v) % MOD;
        return *this;
    }

    ModNum& operator/=(const ModNum& o) {
        return *this *= o.inv();
    }

    friend ModNum operator+(const ModNum& a, const ModNum& b) {
        return ModNum(a) += b;
    }

    friend ModNum operator-(const ModNum& a, const ModNum& b) {
        return ModNum(a) -= b;
    }

    friend ModNum operator*(const ModNum& a, const ModNum& b) {
        return ModNum(a) *= b;
    }

    friend ModNum operator/(const ModNum& a, const ModNum& b) {
        return ModNum(a) /= b;
    }

    friend ModNum operator+(const ModNum& a, int b) {
        return a + ModNum(b);
    }

    friend ModNum operator-(const ModNum& a, int b) {
        return a - ModNum(b);
    }

    friend ModNum operator*(const ModNum& a, int b) {
        return a * ModNum(b);
    }

    friend ModNum operator/(const ModNum& a, int b) {
        return a / ModNum(b);
    }

    friend ModNum operator+(int a, const ModNum& b) {
        return ModNum(a) + b;
    }

    friend ModNum operator-(int a, const ModNum& b) {
        return ModNum(a) - b;
    }

    friend ModNum operator*(int a, const ModNum& b) {
        return ModNum(a) * b;
    }

    friend ModNum operator/(int a, const ModNum& b) {
        return ModNum(a) / b;
    }

    friend ModNum operator+(const ModNum& a, ll b) {
        return a + ModNum(b);
    }

    friend ModNum operator-(const ModNum& a, ll b) {
        return a - ModNum(b);
    }

    friend ModNum operator*(const ModNum& a, ll b) {
        return a * ModNum(b);
    }

    friend ModNum operator/(const ModNum& a, ll b) {
        return a / ModNum(b);
    }

    friend ModNum operator+(ll a, const ModNum& b) {
        return ModNum(a) + b;
    }

    friend ModNum operator-(ll a, const ModNum& b) {
        return ModNum(a) - b;
    }

    friend ModNum operator*(ll a, const ModNum& b) {
        return ModNum(a) * b;
    }

    friend ModNum operator/(ll a, const ModNum& b) {
        return ModNum(a) / b;
    }
};
