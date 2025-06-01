class Solution final {
public:
    constexpr string longestCommonPrefix(
        const vector<string> &strs
    ) const noexcept {
        auto result{0UZ};
        while (true) {
            for (const auto &str : strs)
                if (result >= size(str) || strs.front()[result] != str[result])
                    return strs.front().substr(0, result);
            ++result;
        }
        return ""s;
    }
};
