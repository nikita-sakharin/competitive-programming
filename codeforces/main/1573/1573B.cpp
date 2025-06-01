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

static ullong operations_count(
    const vector<ullong> &,
    const vector<ullong> &
) noexcept;

int main() {
    ios_base::sync_with_stdio(false);
    cerr.tie(nullptr);
    cin.tie(nullptr);

    ullong t;
    cin >> t;
    vector<ullong> a, b;
    while (t--) {
        size_t n;
        cin >> n;
        a.resize(n);
        b.resize(n);
        for (ullong &a_i : a)
            cin >> a_i;
        for (ullong &b_i : b)
            cin >> b_i;
        cout << operations_count(a, b) << '\n';
    }

    return 0;
}

static ullong operations_count(
    const vector<ullong> &a,
    const vector<ullong> &b
) noexcept {
    const size_t size = a.size();
    vector<size_t> min_indices(size);
    for (size_t i = 0; i < size; ++i)
        min_indices[b[i] / 2 - 1] = i;
    for (size_t i = size - 1; i > 0; --i)
        if (min_indices[i - 1] > min_indices[i])
            min_indices[i - 1] = min_indices[i];
    ullong result = size;
    for (size_t i = 0; i < size; ++i)
        result = min(result, static_cast<ullong>(i) + min_indices[a[i] / 2]);
    return result;
}
