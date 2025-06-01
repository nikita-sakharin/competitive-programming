class Solution final {
public:
    constexpr int removeElement(
        vector<int> &nums,
        const int val
    ) const noexcept {
        const auto length{size(nums)};
        auto newlength{0UZ};
        for (auto i{0UZ}; i < length; ++i)
            if (nums[i] != val)
                nums[newlength++] = nums[i];
        nums.resize(newlength);
        return int(newlength);
    }
};
