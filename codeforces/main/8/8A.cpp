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

static bool string_pair_search(
    const string &, const string &, const string &
) noexcept;

int main() {
    ios_base::sync_with_stdio(false);
    cerr.tie(nullptr);
    cin.tie(nullptr);

    string flags, first, second;
    cin >> flags >> first >> second;
    const bool is_find = string_pair_search(flags, first, second);
    reverse(flags.begin(), flags.end());
    const bool is_rfind = string_pair_search(flags, first, second);

    if (is_find && is_rfind)
        cout << "both";
    else if (is_find)
        cout << "forward";
    else if (is_rfind)
        cout << "backward";
    else
        cout << "fantasy";
    cout << '\n';

    return 0;
}

static bool string_pair_search(
    const string &haystack,
    const string &first_needle,
    const string &second_needle
) noexcept {
    const boyer_moore_horspool_searcher
        first_searcher(first_needle.cbegin(), first_needle.cend()),
        second_searcher(second_needle.cbegin(), second_needle.cend());
    auto citer = search(haystack.cbegin(), haystack.cend(), first_searcher);
    if (citer != haystack.cend())
        citer += first_needle.size();
    return search(citer, haystack.cend(), second_searcher) != haystack.cend();
}
