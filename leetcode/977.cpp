class Solution final {
public:
    constexpr vector<int> sortedSquares(
        const vector<int> &nums
    ) const noexcept {
        auto index{size(nums)};
        vector<int> result(index);
        ptrdiff_t i{0}, j(index - 1);
        while (i <= j) {
            const auto productI{nums[size_t(i)] * nums[size_t(i)]},
                productJ{nums[size_t(j)] * nums[size_t(j)]};
            if (productI < productJ) {
                result[--index] = productJ;
                --j;
            } else {
                result[--index] = productI;
                ++i;
            }
        }
        return result;
    }
};
