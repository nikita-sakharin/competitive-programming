class Solution final {
private:
    struct Compare final {
    public:
        constexpr bool operator()(
            const pair<int, string_view> &lhs,
            const int rhs
        ) const noexcept {
            return lhs.first > rhs;
        }
    };

    static constexpr array<pair<int, string_view>, 13> numerals{{
        {1000, "M"}, {900, "CM"},
        {500, "D"}, {400, "CD"},
        {100, "C"}, {90, "XC"},
        {50, "L"}, {40, "XL"},
        {10, "X"}, {9, "IX"},
        {5, "V"}, {4, "IV"},
        {1, "I"}
    }};

    static constexpr const pair<int, string_view> &mostNumeral(
        const int integer
    ) noexcept {
        return *lower_bound(cbegin(numerals), cend(numerals), integer,
            Compare{}
        );
    }

public:
    constexpr string intToRoman(int integer) const noexcept {
        string result{};
        while (integer > 0) {
            const auto [value, numeral] = mostNumeral(integer);
            integer -= value;
            result += numeral;
        }

        return result;
    }
};
