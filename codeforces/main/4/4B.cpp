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

static vector<ullong> get_schedule(
    ullong,
    const vector<pair<ullong, ullong>> &
);

int main() {
    ios_base::sync_with_stdio(false);
    cerr.tie(nullptr);
    cin.tie(nullptr);

    ullong d, sum_time;
    cin >> d >> sum_time;
    vector<pair<ullong, ullong>> time(d);
    for (auto &[min_time, max_time] : time)
        cin >> min_time >> max_time;
    try {
        const vector<ullong> schedule = get_schedule(sum_time, time);
        cout << "YES\n";
        for (const ullong schedule_i : schedule)
            cout << schedule_i << ' ';
        cout << '\n';
    } catch (...) {
        cout << "NO\n";
    }

    return 0;
}

static vector<ullong> get_schedule(
    ullong sum_time,
    const vector<pair<ullong, ullong>> &time
) {
    const size_t d = time.size();
    ullong min_sum = 0, max_sum = 0;
    for (const auto [min_time, max_time] : time) {
        min_sum += min_time;
        max_sum += max_time;
    }
    if (sum_time < min_sum || sum_time > max_sum)
        throw exception();

    vector<ullong> schedule(d);
    schedule.clear();
    for (const auto [min_time, max_time] : time) {
        const ullong diff_sum = max_sum - min_sum,
            diff_time = max_time - min_time;
        const ldbl relative = static_cast<ldbl>(sum_time - min_sum) / diff_sum;
        schedule.push_back(min_time);
        if (diff_sum != 0)
            schedule.back() += llround(relative * diff_time);
        sum_time -= schedule.back();
        min_sum -= min_time;
        max_sum -= max_time;
    }

    return schedule;
}
