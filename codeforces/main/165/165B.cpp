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

template<typename T, typename Predicate>
static constexpr T binary_search(T, T, Predicate) noexcept;

int main() {
    ios_base::sync_with_stdio(false);
    cerr.tie(nullptr);
    cin.tie(nullptr);

    ullong n, k;
    cin >> n >> k;
    cout << ::binary_search(1ULL, n,
        [n, k](const ullong v) constexpr noexcept -> bool {
            ullong sum = 0;
            for (ullong power = 1; v / power != 0; power *= k)
                sum += v / power;
            return sum >= n;
        }
    ) << '\n';

    return 0;
}

template<typename T, typename Predicate>
static constexpr T binary_search(T a, T b, Predicate predicate) noexcept {
    while (a != b) {
        const T middle(midpoint(a, b));
        if (predicate(middle))
            b = middle;
        else
            a = middle + 1;
    }
    return a;
}
