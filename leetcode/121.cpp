class Solution final {
public:
    constexpr int maxProfit(const vector<int> &prices) const noexcept {
        auto minPrice{prices.front()}, result{0};
        for (const auto price : prices) {
            minPrice = min(minPrice, price);
            result = max(result, price - minPrice);
        }

        return result;
    }
};
