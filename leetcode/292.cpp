class Solution final {
public:
    constexpr bool canWinNim(const int n) const noexcept {
        return (n & 0X3) != 0;
    }
};
