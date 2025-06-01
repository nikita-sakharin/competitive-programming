#include <cstddef>

#include <limits>
#include <stdexcept>
#include <vector>

using namespace std;

template<typename T>
static inline vector<vector<ptrdiff_t>> floyd_warshall(vector<vector<T>> &d) {
    static constexpr T infinity = numeric_limits<T>::infinity();

    const auto n{d.size()};
    vector<vector<ptrdiff_t>> pi(n);
    for (size_t i{0}; i < n; ++i) {
        pi[i].resize(n);
        for (size_t j{0}; j < n; ++j)
            pi[i][j] = i == j || d[i][j] == infinity ? -1 : i;
    }
    for (size_t k{0}; k < n; ++k)
        for (size_t i{0}; i < n; ++i)
            for (size_t j{0}; j < n; ++j)
                if (d[i][k] != infinity && d[k][j] != infinity
                    && d[i][k] + d[k][j] < d[i][j]
                ) {
                    d[i][j] = d[i][k] + d[k][j];
                    pi[i][j] = pi[k][j];
                }
    if constexpr (numeric_limits<T>::is_signed)
        for (size_t i{0}; i < n; ++i)
            if (d[i][i] < 0)
                throw invalid_argument();
    return pi;
}
