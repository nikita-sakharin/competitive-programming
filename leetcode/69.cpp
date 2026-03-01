class Solution final {
private:
    using uint = unsigned;

    template<class T>
    static constexpr T isqrt(const T n) noexcept {
        if (n <= T{1})
            return n;

        const auto exponent{(bit_width(T(n - 1)) + 1) >> 1};
        T iCurrent{0}, iNext{T(T{1} << exponent)};
        do {
            iCurrent = iNext;
            iNext = T((iCurrent + n / iCurrent) >> 1);
        } while (iNext < iCurrent);

        return iCurrent;
    }

public:
    constexpr int mySqrt(const int x) const noexcept {
        return isqrt(uint(x));
    }
};
