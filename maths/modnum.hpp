#pragma once

#include <istream>
#include <ostream>

template <int MOD>
class ModNum {
    static_assert(MOD > 1, "MOD must be greater than 1");

private:
    int v;

public:
    constexpr ModNum();
    constexpr ModNum(long long value);

    static constexpr int GetMod();

    constexpr explicit operator int() const;
    constexpr explicit operator long long() const;

    [[nodiscard]] constexpr ModNum GetInv() const;

    [[nodiscard]] constexpr ModNum operator-() const;

    constexpr ModNum& operator++();
    constexpr ModNum operator++(int);
    constexpr ModNum& operator--();
    constexpr ModNum operator--(int);

    constexpr ModNum& operator+=(const ModNum& o);
    constexpr ModNum& operator-=(const ModNum& o);
    constexpr ModNum& operator*=(const ModNum& o);
    constexpr ModNum& operator/=(const ModNum& o);

    // Hidden friends: kept inline so that implicit int/long long -> ModNum
    // conversions work on both operands (e.g. 4 + Mod(3)). They only forward to
    // the out-of-line member implementations.
    friend std::ostream& operator<<(std::ostream& o, const ModNum& x) {
        return o << x.v;
    }

    friend std::istream& operator>>(std::istream& i, ModNum& x) {
        long long val;
        i >> val;
        x = ModNum(val);
        return i;
    }

    [[nodiscard]] friend constexpr bool operator==(const ModNum& a, const ModNum& b) {
        return a.v == b.v;
    }

    [[nodiscard]] friend constexpr bool operator!=(const ModNum& a, const ModNum& b) {
        return a.v != b.v;
    }

    [[nodiscard]] friend constexpr ModNum operator+(ModNum a, const ModNum& b) {
        return a += b;
    }

    [[nodiscard]] friend constexpr ModNum operator-(ModNum a, const ModNum& b) {
        return a -= b;
    }

    [[nodiscard]] friend constexpr ModNum operator*(ModNum a, const ModNum& b) {
        return a *= b;
    }

    [[nodiscard]] friend constexpr ModNum operator/(ModNum a, const ModNum& b) {
        return a /= b;
    }
};

template <int MOD, typename U>
[[nodiscard]] constexpr ModNum<MOD> ComputePower(ModNum<MOD> x, U pw) {
    ModNum<MOD> result(1);
    for (; pw > 0; pw >>= 1) {
        if (pw & 1) {
            result *= x;
        }
        x *= x;
    }
    return result;
}

template <int MOD>
constexpr ModNum<MOD>::ModNum() : v(0) {
}

template <int MOD>
constexpr ModNum<MOD>::ModNum(long long value) : v(static_cast<int>((value % MOD + MOD) % MOD)) {
}

template <int MOD>
constexpr int ModNum<MOD>::GetMod() {
    return MOD;
}

template <int MOD>
constexpr ModNum<MOD>::operator int() const {
    return v;
}

template <int MOD>
constexpr ModNum<MOD>::operator long long() const {
    return v;
}

template <int MOD>
constexpr ModNum<MOD> ModNum<MOD>::GetInv() const {
    return ComputePower(*this, MOD - 2);
}

template <int MOD>
constexpr ModNum<MOD> ModNum<MOD>::operator-() const {
    return v ? ModNum(MOD - v) : ModNum(0);
}

template <int MOD>
constexpr ModNum<MOD>& ModNum<MOD>::operator++() {
    if (++v == MOD) {
        v = 0;
    }
    return *this;
}

template <int MOD>
constexpr ModNum<MOD> ModNum<MOD>::operator++(int) {
    ModNum aux(*this);
    ++(*this);
    return aux;
}

template <int MOD>
constexpr ModNum<MOD>& ModNum<MOD>::operator--() {
    if (--v < 0) {
        v = MOD - 1;
    }
    return *this;
}

template <int MOD>
constexpr ModNum<MOD> ModNum<MOD>::operator--(int) {
    ModNum aux(*this);
    --(*this);
    return aux;
}

template <int MOD>
constexpr ModNum<MOD>& ModNum<MOD>::operator+=(const ModNum& o) {
    if ((v += o.v) >= MOD) {
        v -= MOD;
    }
    return *this;
}

template <int MOD>
constexpr ModNum<MOD>& ModNum<MOD>::operator-=(const ModNum& o) {
    if ((v -= o.v) < 0) {
        v += MOD;
    }
    return *this;
}

template <int MOD>
constexpr ModNum<MOD>& ModNum<MOD>::operator*=(const ModNum& o) {
    v = static_cast<int>(static_cast<long long>(v) * o.v % MOD);
    return *this;
}

template <int MOD>
constexpr ModNum<MOD>& ModNum<MOD>::operator/=(const ModNum& o) {
    return *this *= o.GetInv();
}
