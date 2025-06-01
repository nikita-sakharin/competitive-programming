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

template<typename V>
static constexpr size_t bucket(const vector<V> &, const V &) noexcept;

static ullong inconvenient_pairs(
    const vector<ullong> &,
    const vector<pair<ullong, ullong>> &
) noexcept;

int main() {
    ios_base::sync_with_stdio(false);
    cerr.tie(nullptr);
    cin.tie(nullptr);

    ullong t;
    cin >> t;
    for (ullong i = 0; i < t; ++i) {
        size_t n, m, k;
        cin >> n >> m >> k;
        vector<ullong> vertical(n), horizontal(m);
        for (ullong &x : vertical)
            cin >> x;
        for (ullong &y : horizontal)
            cin >> y;
        vector<pair<ullong, ullong>> persons(k);
        for (auto &[x, y] : persons)
            cin >> x >> y;
        ullong result = 0U;

        sort(persons.begin(), persons.end());
        result += inconvenient_pairs(horizontal, persons);

        for (auto &[x, y] : persons)
            swap(x, y);

        sort(persons.begin(), persons.end());
        result += inconvenient_pairs(vertical, persons);

        cout << result << '\n';
    }

    return 0;
}

template<typename V>
static constexpr size_t bucket(
    const vector<V> &container,
    const V &value
) noexcept {
    return lower_bound(container.cbegin(), container.cend(), value) -
        container.cbegin();
}

static ullong inconvenient_pairs(
    const vector<ullong> &streets,
    const vector<pair<ullong, ullong>> &persons
) noexcept {
    const size_t m = streets.size();
    vector<size_t> buckets(m - 1U);
    for (const auto [x, y] : persons) {
        const size_t bucket_index = bucket(streets, y);
        assert(bucket_index < m);
        if (y == streets[bucket_index])
            continue;
        assert(bucket_index >= 1U);
        ++buckets[bucket_index - 1U];
    }

    const size_t k = persons.size();
    ullong returns = 0U;
    for (size_t i = 0; i < k; ++i) {
        const auto [x, y] = persons[i];
        const size_t bucket_index = bucket(streets, y);
        assert(bucket_index < m);
        if (y == streets[bucket_index])
            continue;
        assert(bucket_index >= 1U);
        const size_t last = lower_bound(
            persons.cbegin() + i + 1, persons.cend(),
            make_pair(x, streets[bucket_index])
        ) - persons.cbegin();
        assert(last <= k);
        returns += buckets[bucket_index - 1U] + i - last;
        --buckets[bucket_index - 1U];
    }

    return returns;
}
