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

static pair<ullong, vector<size_t>> max_capacity(
    ullong,
    const vector<pair<ullong, ullong>> &
) noexcept;

int main() {
    ios_base::sync_with_stdio(false);
    cerr.tie(nullptr);
    cin.tie(nullptr);

    ullong n, v;
    cin >> n >> v;
    vector<pair<ullong, ullong>> t_p(n);
    for (auto &[t, p] : t_p)
        cin >> t >> p;
    const auto [capacity, indexes] = max_capacity(v, t_p);
    cout << capacity << '\n';
    for (const size_t idx : indexes)
        cout << idx + 1 << ' ';
    cout << '\n';

    return 0;
}

static pair<ullong, vector<size_t>> max_capacity(
    ullong v,
    const vector<pair<ullong, ullong>> &t_p
) noexcept {
    const size_t n = t_p.size();
    vector<size_t> indexes(n);
    iota(indexes.begin(), indexes.end(), 0);
    sort(indexes.begin(), indexes.end(),
        [&t_p](const size_t i, const size_t j) noexcept -> bool {
            const auto [t_i, p_i] = t_p[i];
            const auto [t_j, p_j] = t_p[j];
            return t_i != t_j ? t_i < t_j : p_i > p_j;
        }
    );
    const size_t idx_2 = find_if(indexes.cbegin(), indexes.cend(),
        [&t_p](const size_t i) noexcept -> bool {
            return t_p[i].first == 2;
        }
    ) - indexes.cbegin();

    ullong capacity = 0;
    vector<size_t> result;
    for (size_t i = 0, j = idx_2; (v > 0 && i < idx_2) || (v > 1 && j < n); ) {
        assert(i <= idx_2 && j <= n);
        if (j == n || (i < idx_2 && v % 2 == 1))
            result.push_back(indexes[i]);
        else if (i < idx_2 && j < n) {
            const size_t i_idx = indexes[i], j_idx = indexes[j];
            const ullong p_i = t_p[i_idx].second, p_j = t_p[j_idx].second,
                p_ip1 = (i + 1 < idx_2 ? t_p[indexes[i + 1]].second : 0);
            result.push_back(p_i + p_ip1 >= p_j ? i_idx : j_idx);
        } else
            result.push_back(indexes[j]);
        const auto [t, p] = t_p[result.back()];
        v -= t;
        capacity += p;
        t == 1 ? ++i : ++j;
    }
    return make_pair(capacity, move(result));
}
