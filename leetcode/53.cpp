class Solution final {
private:
    template<class T>
    static constexpr auto minV{numeric_limits<T>::min()};

public:
    constexpr int maxSubArray(const vector<int> &nums) const noexcept {
        auto sum{0}, result{minV<int>};
        for (const auto num : nums) {
            sum = max(num, sum + num);
            result = max(result, sum);
        }

        return result;
    }
};
