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

static constexpr ullong m = 998244353ULL;

static ullong permutations_count(const vector<ullong> &) noexcept;
static constexpr ullong product(ullong, ullong) noexcept;

int main() {
    ios_base::sync_with_stdio(false);
    cerr.tie(nullptr);
    cin.tie(nullptr);

    ullong t;
    cin >> t;
    for (ullong i = 0; i < t; ++i) {
        size_t n;
        cin >> n;
        vector<ullong> p(n);
        for (ullong &p_i : p)
            cin >> p_i;
        sort(p.begin(), p.end(), greater<ullong>());
        cout << permutations_count(p) << '\n';
    }

    return 0;
}

static ullong permutations_count(const vector<ullong> &p) noexcept {
    assert(is_sorted(p.cbegin(), p.cend(), greater<ullong>()));

    const ullong diff = p[0] - p[1];
    if (diff > 1LL)
        return 0;
    const size_t size = p.size();
    if (diff == 0LL)
        return product(1LL, size);
    const size_t second_count = count(p.cbegin(), p.cend(), p[1]);
    ullong returns = second_count;
    returns *= product(1LL, second_count);
    returns %= m;
    returns *= product(second_count + 2LL, size);
    returns %= m;
    return returns;
}

static constexpr ullong product(ullong from, const ullong to) noexcept {
    ullong returns = 1LL;
    while (from <= to) {
        returns *= from++;
        returns %= m;
    }
    return returns;
}
