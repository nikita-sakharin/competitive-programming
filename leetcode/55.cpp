class Solution final {
public:
    constexpr bool canJump(const vector<int> &nums) const noexcept {
        const auto length{size(nums)};
        for (auto i{0UZ}, maxI{0UZ}; i < length; ++i) {
            if (i > maxI)
                return false;
            maxI = max(maxI, i + min(length - i, size_t(nums[i])));
        }
        return true;
    }
};
