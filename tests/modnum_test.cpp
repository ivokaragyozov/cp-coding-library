#include <cassert>
#include <sstream>

#include "maths/modnum.hpp"

using Mod = ModNum<1000000007>;

int main() {
    // Construction and equality
    assert(Mod(0) == Mod(0));
    assert(Mod(5) == Mod(5));
    assert(Mod(5) != Mod(6));
    assert(Mod(-1) == Mod(1000000006));
    assert(Mod(1000000007) == Mod(0));
    assert(Mod(2000000014LL) == Mod(0));

    // Arithmetic
    assert(Mod(3) + Mod(4) == Mod(7));
    assert(Mod(1000000006) + Mod(1) == Mod(0));
    assert(Mod(3) - Mod(5) == Mod(1000000005));
    assert(Mod(3) * Mod(4) == Mod(12));
    assert(Mod(6) / Mod(2) == Mod(3));

    // Mixed int/ll arithmetic via implicit construction
    assert(Mod(3) + 4 == Mod(7));
    assert(4 + Mod(3) == Mod(7));
    assert(Mod(3) * 4 == Mod(12));
    assert(4 * Mod(3) == Mod(12));

    // Compound assignment
    Mod x(5);
    x += Mod(3);
    assert(x == Mod(8));
    x -= Mod(10);
    assert(x == Mod(1000000005));
    x *= Mod(2);
    assert(x == Mod(1000000003));
    x /= Mod(2);
    assert(x == Mod(1000000005));

    // Increment / decrement
    Mod y(0);
    assert(y++ == Mod(0));
    assert(y == Mod(1));
    assert(++y == Mod(2));

    Mod z(0);
    assert(z-- == Mod(0));
    assert(z == Mod(1000000006));
    assert(--z == Mod(1000000005));

    // Unary minus
    assert(-Mod(0) == Mod(0));
    assert(-Mod(1) == Mod(1000000006));

    // ComputePower
    assert(ComputePower(Mod(2), 10) == Mod(1024));
    assert(ComputePower(Mod(2), 0) == Mod(1));

    // GetInv
    assert(Mod(2).GetInv() == Mod(500000004));
    assert(Mod(2) * Mod(2).GetInv() == Mod(1));

    // Explicit cast
    assert((int)Mod(42) == 42);
    assert((long long)Mod(42) == 42LL);

    // Stream I/O
    std::ostringstream oss;
    oss << Mod(42);
    assert(oss.str() == "42");

    std::istringstream iss("1000000008");
    Mod w;
    iss >> w;
    assert(w == Mod(1));

    return 0;
}
