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

    llong n, p1, p2, p3, t1, t2;
    cin >> n >> p1 >> p2 >> p3 >> t1 >> t2;

    llong sum = 0;
    for (llong i = 0, r, in_p1, in_p2, in_p3; i < n; ++i) {
        llong l;
        cin >> l;
        const llong diff = (i == 0 ? 0 : l - r);
        cin >> r;
        in_p1 = min(diff, t1);
        in_p2 = min(max(diff - in_p1, 0LL), t2);
        in_p3 = max(diff - in_p1 - in_p2, 0LL);
        sum += (r - l + in_p1) * p1 + in_p2 * p2 + in_p3 * p3;
    }
    cout << sum << '\n';

    return 0;
}
