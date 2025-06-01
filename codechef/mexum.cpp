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

static constexpr ullong maxN{100'000L}, mod{998'244'353L};

template<class Producer, class Consumer>
static inline void mexum(ullong, Producer, Consumer) noexcept;
template<class Arithmetic>
static inline vector<Arithmetic> power(Arithmetic, size_t) noexcept;

int main() {
    ios_base::sync_with_stdio(false);
    cerr.tie(nullptr);
    cin.tie(nullptr);

    ullong t;
    cin >> t;
    mexum(
        t,
        [](vector<ullong> &a) noexcept -> void {
            size_t n;
            cin >> n;
            a.resize(n);
            for (auto &aI : a)
                cin >> aI;
        },
        [](const ullong result) noexcept -> void {
            cout << result << '\n';
        }
    );
    return 0;
}

template<class Producer, class Consumer>
static inline void mexum(
    ullong t,
    Producer producer,
    Consumer consumer
) noexcept {
    const vector<ullong> pows{power(2ULL, maxN + 1)};
    vector<ullong> a(maxN);
    vector<size_t> count(maxN + 2);

    for (; t != 0; --t) {
        producer(a);
        const auto size{a.size()}, limit{size + 2};
        count.assign(limit, 0);
        for (const ullong maxMex{size + 1}; const auto aI : a)
            ++count[min(aI, maxMex)];

        ullong result{0}, product{1};
        for (size_t i{1}, sum{size}; i < limit; ++i) {
            sum -= count[i];
            result = (result + product * pows[sum] % mod * i % mod) % mod;
            product = product * (pows[count[i]] - 1) % mod;
        }
        consumer(result);
    }
}

template<class Arithmetic>
static inline vector<Arithmetic> power(
    const Arithmetic x,
    const size_t n
) noexcept {
    vector<Arithmetic> result(n);
    if (n != 0)
        result[0] = 1;
    for (size_t i{1}; i < n; ++i)
        result[i] = result[i - 1] * x % mod;
    return result;
}
