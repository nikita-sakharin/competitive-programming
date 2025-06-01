class Solution final {
public:
    constexpr int maxProfit(const vector<int> &prices) const noexcept {
        const auto length{size(prices)};
        auto result{0};
        for (auto i{1UZ}; i < length; ++i)
            result += max(0, prices[i] - prices[i - 1]);

        return result;
    }
};
