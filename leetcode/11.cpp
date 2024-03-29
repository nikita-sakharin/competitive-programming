class Solution final {
public:
    constexpr int maxArea(const vector<int> &height) const noexcept {
        auto result{0};
        ptrdiff_t i{0}, j(height.size() - 1);
        while (i < j) {
            const auto width{int(j - i)},
                minHeight{height[i] < height[j] ? height[i++] : height[j--]};
            result = max(result, width * minHeight);
        }
        return result;
    }
};
