class Solution final {
private:
    using uint = unsigned;

public:
    constexpr int hammingDistance(const int x, const int y) const noexcept {
        return popcount(uint(x ^ y));
    }
};
