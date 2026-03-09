class Solution final {
private:
    template<class T>
    static constexpr bool isEven(const T value) noexcept {
        return !(value & T{1});
    }

public:
    constexpr bool divisorGame(const int n) const noexcept {
        return isEven(n);
    }
};
