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

static ostream &find_king_path(ostream &, llong, llong);

int main() {
    ios_base::sync_with_stdio(false);
    cerr.tie(nullptr);
    cin.tie(nullptr);

    char x_s, x_t;
    llong y_s, y_t;
    cin >> x_s >> y_s >> x_t >> y_t;
    find_king_path(cout, x_t - x_s, y_t - y_s);

    return 0;
}

static ostream &find_king_path(ostream &os, llong dx, llong dy) {
    os << max(abs(dx), abs(dy)) << '\n';
    while (dx != 0 || dy != 0) {
        if (dx < 0) {
            ++dx;
            os << 'L';
        } else if (dx > 0) {
            --dx;
            os << 'R';
        }
        if (dy < 0) {
            ++dy;
            os << 'D';
        } else if (dy > 0) {
            --dy;
            os << 'U';
        }
        os << '\n';
    }
    return os;
}
