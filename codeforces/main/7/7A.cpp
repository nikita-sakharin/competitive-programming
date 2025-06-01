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

int main() {
    ios_base::sync_with_stdio(false);
    cerr.tie(nullptr);
    cin.tie(nullptr);

    static constexpr size_t eight = 8U;

    array<array<bool, eight>, eight> board;
    for (array<bool, eight> &row : board)
        for (bool &square : row) {
            char c;
            cin >> c;
            square = (c == 'B');
        }

    size_t row_count = 0, column_count = 0;
    for_each(board.cbegin(), board.cend(),
        [&row_count, &column_count](
            const array<bool, eight> &row
        ) noexcept -> void {
            const size_t black_count = count(row.cbegin(), row.cend(), true);
            if (black_count == eight)
                ++row_count;
            else
                column_count = black_count;
        }
    );
    cout << row_count + column_count << '\n';

    return 0;
}
