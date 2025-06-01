class Solution final {
private:
    template<class T>
    static constexpr auto
        width{numeric_limits<T>::is_signed + numeric_limits<T>::digits};

    template<class T>
    static constexpr T add(const T a, const T b) noexcept {
        auto p{(a | b) << 1}, c{(a & b) << 1};
        for (auto shift{1}; shift < width<T>; shift <<= 1) {
            c |= p & (c << shift);
            p &= p << shift;
        }

        return a ^ b ^ c;
    }

public:
    constexpr int getSum(const int a, const int b) const noexcept {
        return add(a, b);
    }
};
