class Solution final {
public:
    constexpr void moveZeroes(vector<int> &nums) const noexcept {
        const auto length{size(nums)};
        auto nonZero{0UZ};
        for (auto i{0UZ}; i < length; ++i)
            if (nums[i] != 0)
                swap(nums[nonZero++], nums[i]);
    }
};
