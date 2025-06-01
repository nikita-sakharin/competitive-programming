class Solution final {
public:
    constexpr int subsetXORSum(const vector<int> &nums) const noexcept {
        const auto count{1 << (size(nums) - 1)};
        return accumulate(cbegin(nums), cend(nums), 0, bit_or{}) * count;
    }
};
