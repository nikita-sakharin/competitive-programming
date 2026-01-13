class Solution final {
private:
    template<class Iter, class Func>
    static constexpr void findPalindromes(
        const Iter first,
        const Iter last,
        Func &&func
    ) noexcept {
        using Difference = iterator_traits<Iter>::difference_type;

        if (first == last)
            return;

        const auto size{distance(first, last)};
        vector<Difference> buffer(size);
        for (const auto isOdd : {false, true}) {
            for (Difference i{!isOdd}, left{0}, right{0}; i < size; ++i) {
                const auto bound{min(i + isOdd, size - i)}, border{right - i};
                auto k{border > 0
                    ? min(buffer[left + border - 1], border)
                    : isOdd
                };
                if (k >= border)
                    while (k < bound && first[i - !isOdd - k] == first[i + k])
                        ++k;
                buffer[i - !isOdd] = k;
                if (i + k > right) {
                    left = i + isOdd - k;
                    right = i + k;
                }
                if (k > 0)
                    func(next(first, i + isOdd - k), next(first, i + k));
            }
        }
    }

public:
    constexpr string longestPalindrome(const string &str) const noexcept {
        string_view result{};
        findPalindromes(cbegin(str), cend(str),
            [&result](
                const auto first,
                const auto last
            ) constexpr noexcept -> void {
                if (distance(first, last) > ssize(result))
                    result = string_view(first, last);
            }
        );

        return string(result);
    }
};
