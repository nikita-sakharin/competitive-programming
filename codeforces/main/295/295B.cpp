#include <cassert>
#include <ccomplex>
#include <cctype>
#include <cerrno>
#include <cfenv>
#include <cfloat>
#include <cinttypes>
#include <ciso646>
#include <climits>
#include <clocale>
#include <cmath>
#include <csetjmp>
#include <csignal>
#include <cstdalign>
#include <cstdarg>
#include <cstdbool>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctgmath>
#include <ctime>
#include <cuchar>
#include <cwchar>
#include <cwctype>

#include <algorithm>
#include <any>
#include <array>
#include <atomic>
#include <bitset>
#include <chrono>
#include <codecvt>
#include <complex>
#include <condition_variable>
#include <deque>
#include <exception>
#include <execution>
#include <filesystem>
#include <forward_list>
#include <fstream>
#include <functional>
#include <future>
#include <initializer_list>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <memory_resource>
#include <mutex>
#include <new>
#include <numeric>
#include <optional>
#include <ostream>
#include <queue>
#include <random>
#include <ratio>
#include <regex>
#include <scoped_allocator>
#include <set>
#include <shared_mutex>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <string_view>
#include <system_error>
#include <thread>
#include <tuple>
#include <type_traits>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <valarray>
#include <variant>
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
static inline vector<T> floydWarshall(
    vector<vector<T>> &,
    const vector<size_t> &
) noexcept;

int main() {
    ios_base::sync_with_stdio(false);
    cerr.tie(nullptr);
    cin.tie(nullptr);

    size_t n;
    cin >> n;
    vector<vector<ullong>> a(n);
    for (auto &aI : a) {
        aI.resize(n);
        for (auto &aIJ : aI)
            cin >> aIJ;
    }
    vector<size_t> x(n);
    for (auto i{ptrdiff_t(n) - 1}; i >= 0; --i) {
        cin >> x[size_t(i)];
        --x[size_t(i)];
    }
    const auto sum{floydWarshall(a, x)};
    for (auto i{ptrdiff_t(n) - 1}; i >= 0; --i)
        cout << sum[size_t(i)] << "\n "[i != 0];

    return 0;
}

template<typename T>
static inline vector<T> floydWarshall(
    vector<vector<T>> &d,
    const vector<size_t> &loc
) noexcept {
    const auto n{d.size()};
    vector<T> sum(n);
    vector<bool> visited(n);
    for (size_t k{0}; k < n; ++k) {
        const auto index{loc[k]};
        visited[index] = true;
        for (size_t i{0}; i < n; ++i)
            for (size_t j{0}; j < n; ++j) {
                d[i][j] = min(d[i][j], d[i][index] + d[index][j]);
                if (visited[i] && visited[j] && i != j)
                    sum[k] += d[i][j];
            }
    }
    return sum;
}
