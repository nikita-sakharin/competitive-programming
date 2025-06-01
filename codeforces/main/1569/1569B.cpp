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

static vector<string> chess_match_results(const vector<bool> &);

int main() {
    ios_base::sync_with_stdio(false);
    cerr.tie(nullptr);
    cin.tie(nullptr);

    ullong t;
    cin >> t;
    for (ullong i = 0; i < t; ++i) {
        ullong n;
        string s;
        cin >> n >> s;
        assert(n == s.size());
        vector<bool> expectations(n);
        transform(s.cbegin(), s.cend(), expectations.begin(),
            [](const char ch) constexpr noexcept -> bool {
                return static_cast<bool>(ch - '1');
            }
        );
        try {
            const vector<string> results = chess_match_results(expectations);
            cout << "YES\n";
            for (const string &result : results)
                cout << result << '\n';
        } catch (...) {
            cout << "NO\n";
        }
    }

    return 0;
}

static vector<string> chess_match_results(const vector<bool> &expectations) {
    const size_t n = expectations.size();
    vector<string> returns(n, string(n, '='));
    vector<size_t> winners;
    for (size_t i = 0; i < n; ++i) {
        returns[i][i] = 'X';
        if (expectations[i])
            winners.push_back(i);
    }
    const size_t size = winners.size();
    if (size >= 1U && size < 3U)
        throw exception();
    for (size_t i = 0; i < size; ++i) {
        const size_t winner = winners[i], loser = winners[(i + 1) % size];
        returns[winner][loser] = '+';
        returns[loser][winner] = '-';
    }
    return returns;
}
