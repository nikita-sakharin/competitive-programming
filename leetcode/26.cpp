class Solution final {
public:
    constexpr int removeDuplicates(vector<int> &nums) const noexcept {
        const auto length{size(nums)};
        auto newLength{1UZ};
        for (auto i{1UZ}; i < length; ++i)
            if (nums[i - 1] != nums[i])
                nums[newLength++] = nums[i];
        nums.resize(newLength);
        return int(newLength);
    }
};
