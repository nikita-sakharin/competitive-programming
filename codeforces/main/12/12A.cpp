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

    static constexpr size_t three = 3;

    array<array<bool, three>, three> matrix;
    for (array<bool, three> &row : matrix)
        for (bool &element : row) {
            char c;
            cin >> c;
            element = c == 'X';
        }

    bool is_symmetric = true;
    for (size_t i = 0; i < three && is_symmetric; ++i)
        for (size_t j = i; j < three && is_symmetric; ++j)
            if (matrix[i][j] != matrix[three - i - 1][three - j - 1])
                is_symmetric = false;
    cout << (is_symmetric ? "YES" : "NO") << '\n';

    return 0;
}
