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

static pair<ullong, string> least_base_path(
    const vector<vector<ullong>> &,
    ullong
);
static pair<ullong, string> least_round_path(const vector<vector<ullong>> &);
static constexpr ullong multiplier_count(ullong, ullong) noexcept;

int main() {
    ios_base::sync_with_stdio(false);
    cerr.tie(nullptr);
    cin.tie(nullptr);

    size_t n;
    cin >> n;
    vector<vector<ullong>> matrix(n, vector<ullong>(n));
    for (vector<ullong> &row : matrix)
        for (ullong &element : row)
            cin >> element;
    const auto [length, path] = least_round_path(matrix);
    cout << length << '\n' << path << '\n';

    return 0;
}

static pair<ullong, string> least_base_path(
    const vector<vector<ullong>> &matrix,
    const ullong base
) {
    const ptrdiff_t n = matrix.size();
    vector<vector<ullong>> counts(n, vector<ullong>(n));
    for (ptrdiff_t i = n - 1; i >= 0; --i)
        for (ptrdiff_t j = n - 1; j >= 0; --j) {
            if (i + 1 < n && j + 1 < n)
                counts[i][j] = min(counts[i + 1][j], counts[i][j + 1]);
            else if (i + 1 < n)
                counts[i][j] = counts[i + 1][j];
            else if (j + 1 < n)
                counts[i][j] = counts[i][j + 1];
            counts[i][j] += multiplier_count(matrix[i][j], base);
        }

    string path;
    for (ptrdiff_t i = 0, j = 0; min(i, j) + 1 < n; )
        if (i + 1 == n || (j + 1 < n && counts[i][j + 1] < counts[i + 1][j])) {
            path.push_back('R');
            ++j;
        } else {
            path.push_back('D');
            ++i;
        }

    return make_pair(counts.front().front(), move(path));
}

static pair<ullong, string> least_round_path(
    const vector<vector<ullong>> &matrix
) {
    const auto [length_2, path_2] = least_base_path(matrix, 2);
    const auto [length_5, path_5] = least_base_path(matrix, 5);
    const ullong length = min(length_2, length_5);
    if (const size_t n = matrix.size(); length > 1)
        for (size_t i = 0; i < n; ++i)
            for (size_t j = 0; j < n; ++j)
                if (matrix[i][j] == 0) {
                    string path(i, 'D');
                    path.resize(path.size() + n - 1, 'R');
                    path.resize(path.size() + n - 1 - i, 'D');
                    return make_pair(1, move(path));
                }
    return make_pair(length, length_5 < length_2 ? path_5 : path_2);
}

static constexpr ullong multiplier_count(
    ullong number,
    const ullong base
) noexcept {
    ullong returns = 0;
    while (number != 0 && number % base == 0) {
        number /= base;
        ++returns;
    }
    return returns;
}
