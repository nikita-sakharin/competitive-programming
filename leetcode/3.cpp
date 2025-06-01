class Solution final {
private:
    static constexpr auto printableChars{95UZ};

    static constexpr size_t order(const char ch) noexcept {
        return ch - ' ';
    }

public:
    constexpr int lengthOfLongestSubstring(const string &str) const noexcept {
        const auto length{size(str)};
        auto result{0UZ};
        bitset<printableChars> chars{};
        for (auto i{0UZ}; i < length; ++i) {
            const auto charOrder{order(str[i])};
            while (chars.test(charOrder))
                chars.reset(order(str[i - chars.count()]));
            chars.set(charOrder);
            result = max(result, chars.count());
        }
        return int(result);
    }
};
