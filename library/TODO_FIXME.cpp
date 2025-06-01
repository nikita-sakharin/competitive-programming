#include <cassert>
#include <cmath>
#include <cstddef>

#include <algorithm>
#include <array>
#include <bitset>
#include <complex>
#include <deque>
#include <exception>
#include <forward_list>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <list>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <queue>
#include <random>
#include <regex>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <valarray>
#include <vector>

using schar  = signed char;
using uchar  = unsigned char;
using shrt   = short;
using ushrt  = unsigned short;
using uint   = unsigned;
using ulong  = unsigned long;
using llong  = long long;
using ullong = unsigned long long;
using flt    = float;
using dbl    = double;
using ldbl   = long double;

using namespace std;

static constexpr llong mod = 1000000007LL;

static constexpr llong binary_pow(llong, llong);
static constexpr llong gcd_extended(llong, llong, llong &, llong &);
static constexpr llong geometric_series(llong, llong, llong);
static constexpr llong inverse_mod(llong);
static constexpr llong sum(llong, llong, llong, llong);

int main() {
    llong q;
    cin >> q;
    for (llong i = 0; i < q; ++i) {
        llong i1, i2, j1, j2;
        cin >> i1 >> i2 >> j1 >> j2;
        cout << sum(i1, i2, j1, j2) << '\n';
    }

    return 0;
}

static constexpr llong binary_pow(llong a, llong n) {
    llong res = 1;
    while (n != 0) {
        if (n & 1) {
            res *= a;
            res %= mod;
        }
        a *= a;
        a %= mod;
        n >>= 1;
    }
    return res;
}

static constexpr llong gcd_extended(
    const llong a, const llong b,
    llong &x, llong &y
) {
    if (a == 0) {
        x = 0;
        y = 1;
        return b;
    }
    llong x1 = 0, y1 = 1;
    const llong d = gcd_extended(b % a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return d;
}

static constexpr llong geometric_series(
    const llong q, const llong b1, const llong n
) {
    const llong first = (mod - binary_pow(q, n) + 1) % mod,
        second = inverse_mod(mod - q + 1);
    return ((b1 * first) % mod * second) % mod;
}

static constexpr llong inverse_mod(const llong a) {
    llong x = 0, y = 1;
    const llong g = gcd_extended(a, mod, x, y);
    if (g != 1)
        return -1;
    return (x % mod + mod) % mod;
}

static constexpr llong sum(
    const llong i1, const llong i2,
    const llong j1, const llong j2
) {
    const llong a_i1_j1 = binary_pow(2, i1) * binary_pow(3, j1) % mod;
    const llong b1 = geometric_series(3, a_i1_j1, j2 - j1 + 1);
    return geometric_series(2, b1, i2 - i1 + 1);
}
