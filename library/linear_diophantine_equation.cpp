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

template<typename T>
struct line {
    T a{}, b{}, c{};
};

template<typename T>
struct point {
    T x{}, y{};
};

static ostream operator<<(ostream &, point) noexcept;

static constexpr point find_point(const line &) noexcept {
    ;
}

int main() {
    ios_base::sync_with_stdio(false);
    cerr.tie(nullptr);
    cin.tie(nullptr);

    line<llong> abc;
    cin >> abc.a >> abc.b >> abc.c;
    cout << find_point(line);

    return 0;
}

static ostream operator<<(ostream &os, const point &xy) noexcept {
    return os << x << ' '<< y;
}

template<typename T>
static constexpr T gcd(T a, T b) {
    T x = 1, y = 0, next_x = 0, next_y = 1;
    while (b) {
        const T q = a / b;
        a %= b;
        swap(a, b);
        x -= q * next_x;
        swap(x, next_x);
        y -= q * next_y;
        swap(y, next_y);
    }
    return make_tuple(a, x, y);
}

template<typename T>
static constexpr T gcd(T a, T b) noexcept {
    while (b != 0) {
        a %= b;
        swap(a, b);
    }
    return a;
}

template<typename T>
static constexpr point<T> linear_diophantine_equation(const line<T> &abc) noexcept {
    return { 0, -line.c / line.b };
}
