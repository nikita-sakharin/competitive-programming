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

static ullong operations_count(const vector<ullong> &, ullong) noexcept;

int main() {
    ios_base::sync_with_stdio(false);
    cerr.tie(nullptr);
    cin.tie(nullptr);

    size_t n;
    ullong d;
    cin >> n >> d;
    vector<ullong> b(n);
    for (ullong &b_i : b)
        cin >> b_i;
    cout << operations_count(b, d) << '\n';

    return 0;
}

static ullong operations_count(
    const vector<ullong> &b,
    const ullong d
) noexcept {
    const size_t n = b.size();
    ullong returns = 0, b_prev = b.front();
    for (size_t i = 1; i < n; ++i) {
        if (b_prev < b[i])
            b_prev = b[i];
        else {
            const ullong count = (b_prev - b[i]) / d + 1;
            returns += count;
            b_prev = b[i] + d * count;
        }
    }

    return returns;
}
