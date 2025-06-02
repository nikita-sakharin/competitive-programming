class Solution final {
private:
    static inline const locale &classic{locale::classic()};

public:
    constexpr bool isPalindrome(const string &str) const noexcept {
        auto i{cbegin(str)}, j{--cend(str)};
        while (i < j) {
            const auto left{*i}, right{*j};
            if (!isalnum(left, classic))
                ++i;
            else if (!isalnum(right, classic))
                --j;
            else if (tolower(left, classic) == tolower(right, classic)) {
                ++i;
                --j;
            } else
                return false;
        }

        return true;
    }
};
