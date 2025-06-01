class Solution final {
public:
    constexpr bool divisorGame(const int n) const noexcept {
        return (n & 1) == 0;
    }
};
