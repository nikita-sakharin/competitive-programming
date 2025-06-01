class Solution final {
private:
    using uint = unsigned;

    static constexpr auto mod{10UZ};
    static constexpr array<int, mod> modInverse{0, 1, 0, 7, 0, 0, 0, 3, 0, 9};
    static constexpr array<int, 4> remainders{6, 2, 4, 8};

    template<class T>
    static constexpr pair<T, uint> factorize(
        T value,
        const T divider
    ) noexcept {
        auto result{0U};
        while (value % divider == T{0}) {
            value /= divider;
            ++result;
        }

        return {value, result};
    }

    template<class Iter>
    static constexpr void pascalTriangleRow(
        Iter first,
        const size_t index
    ) noexcept {
        using Value = iterator_traits<Iter>::value_type;

        Value binomial{1};
        *first++ = binomial;
        for (auto k{0UZ}, exp2{0UZ}, exp5{0UZ}; k < index; ++first, ++k) {
            auto multiplier{index - k}, divider{k + 1};
            auto diff{0U};

            const auto multiplierTwos{uint(countr_zero(multiplier))};
            exp2 += multiplierTwos;
            multiplier >>= multiplierTwos;
            tie(multiplier, diff) = factorize(multiplier, 5UZ);
            exp5 += diff;
            binomial = binomial * Value(multiplier) % Value{mod};

            const auto dividerTwos{uint(countr_zero(divider))};
            exp2 -= dividerTwos;
            divider >>= dividerTwos;
            tie(divider, diff) = factorize(divider, 5UZ);
            exp5 -= diff;
            binomial = binomial * modInverse[divider % mod] % Value{mod};

            if (exp2 == 0 && exp5 == 0)
                *first = binomial;
            else if (exp2 != 0 && exp5 == 0)
                *first = binomial * remainders[exp2 & 0X3] % Value{mod};
            else if (exp2 == 0 && exp5 != 0)
                *first = binomial * Value{5} % Value{mod};
            else
                *first = Value{0};
        }
    }

public:
    constexpr int triangularSum(const vector<int> &values) const noexcept {
        const auto length{size(values)};
        vector<int> row(length);
        pascalTriangleRow(begin(row), length - 1);
        auto result{0};
        for (auto i{0UZ}; i < length; ++i)
            result = (result + values[i] * row[i]) % int{mod};

        return result;
    }
};
