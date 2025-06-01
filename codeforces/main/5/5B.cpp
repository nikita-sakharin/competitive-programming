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

    vector<string> text;
    size_t max_size = 0;
    while (text.push_back(""), getline(cin, text.back()))
        max_size = max(max_size, text.back().size());
    text.pop_back();

    const string frame(max_size + 2, '*');
    cout << frame << '\n';
    bool to_right = false;
    for (const string &line : text) {
        cout << '*';
        const size_t spaces = max_size - line.size();
        for (size_t i = 0; i < (spaces + to_right) / 2; ++i)
            cout << ' ';
        cout << line;
        for (size_t i = 0; i < (spaces + !to_right) / 2; ++i)
            cout << ' ';
        cout << "*\n";
        if (spaces % 2 == 1)
            to_right = !to_right;
    }
    cout << frame << '\n';

    return 0;
}
