class Solution final {
public:
    constexpr int findMin(const vector<int> &nums) const noexcept {
        return *upper_bound(cbegin(nums), cend(nums), nums.back(),
            greater_equal<int>{}
        );
    }
};
