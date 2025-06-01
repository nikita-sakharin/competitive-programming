class Solution final {
public:
    constexpr int maxArea(const vector<int> &height) const noexcept {
        auto result{0};
        auto i{cbegin(height)}, j{--cend(height)};
        while (i != j) {
            const auto width{int(distance(i, j))},
                minHeight{*i < *j ? *i++ : *j--};
            result = max(result, width * minHeight);
        }

        return result;
    }
};
