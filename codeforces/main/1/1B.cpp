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

static string transform_numeration(const string &) noexcept;

int main() {
    ios_base::sync_with_stdio(false);
    cerr.tie(nullptr);
    cin.tie(nullptr);

    ullong n;
    cin >> n;
    for (string input; n > 0; --n) {
        cin >> input;
        cout << transform_numeration(input) << '\n';
    }

    return 0;
}

static string transform_numeration(const string &input) noexcept {
    static constexpr size_t letters_count = 26;
    static const regex first("([A-Z]+)(\\d+)", regex_constants::optimize),
        second("R(\\d+)C(\\d+)", regex_constants::optimize);

    string returns;
    if (smatch m; regex_match(input, m, second)) {
        ullong col = stoull(m[2]);
        assert(col > 0);
        do {
            --col;
            returns += col % letters_count + 'A';
            col /= letters_count;
        } while (col != 0);
        reverse(returns.begin(), returns.end());
        returns += m[1];
    } else if (regex_match(input, m, first)) {
        ullong col = 0;
        for (const char c : m[1].str()) {
            assert(c >= 'A' && c <= 'Z');
            col *= letters_count;
            col += c - 'A' + 1;
        }
        returns = 'R';
        returns += to_string(stoull(m[2]));
        returns += 'C';
        returns += to_string(col);
    } else assert(false);
    return returns;
}
