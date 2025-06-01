class Solution final {
public:
    constexpr bool isPowerOfTwo(const int n) const noexcept {
        return n > 0 && (n & (n - 1)) == 0;
    }
};
