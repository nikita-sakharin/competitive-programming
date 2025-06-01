class Solution final {
public:
    constexpr int largestSubmatrix(
        vector<vector<int>> &matrix
    ) const noexcept {
        const auto m{size(matrix)}, n{size(matrix.front())};
        for (auto i{1UZ}; i < m; ++i)
            for (auto j{0UZ}; j < n; ++j)
                if (matrix[i][j] != 0)
                    matrix[i][j] = matrix[i - 1][j] + 1;
        auto result{0};
        for (auto i{0UZ}; i < m; ++i) {
            sort(begin(matrix[i]), end(matrix[i]));
            for (auto j{0UZ}; j < n; ++j)
                result = max(result, matrix[i][n - j - 1] * int(j + 1));
        }
        return result;
    }
};
