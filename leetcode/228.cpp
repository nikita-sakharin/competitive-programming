class Solution final {
private:
    static constexpr void pushBack(
        vector<string> &result,
        const int first,
        const int second
    ) noexcept {
        result.push_back(to_string(first));
        if (first != second)
            result.back().append("->").append(to_string(second));
    }

public:
    constexpr vector<string> summaryRanges(
        const vector<int> &nums
    ) const noexcept {
        const auto length{size(nums)};
        vector<string> result{};
        if (length == 0)
            return result;
        auto left{nums.front()};
        for (auto i{1UZ}; i < length; ++i)
            if (const auto prev{nums[i - 1]}; nums[i] != prev + 1) {
                pushBack(result, left, prev);
                left = nums[i];
            }
        pushBack(result, left, nums.back());
        return result;
    }
};
