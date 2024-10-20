class Solution final {
private:
    template<class Iter, class Func>
    static constexpr void findPalindromes(
        const Iter first,
        const Iter last,
        Func func
    ) noexcept {
        using Difference = iterator_traits<Iter>::difference_type;

        if (first == last)
            return;
        const auto size{distance(first, last)};
        vector<Difference> buffer(size);
        for (const bool isOdd : {false, true}) {
            for (Difference i{!isOdd}, left{0}, right{0}; i < size; ++i) {
                const auto bound{min(i + isOdd, size - i)};
                auto k{i >= right
                    ? isOdd
                    : min(buffer[left + (right - 1 - i)], right - i)
                };
                while (k < bound && first[i - !isOdd - k] == first[i + k])
                    ++k;
                buffer[i - !isOdd] = k;
                if (i + k > right) {
                    left = i + isOdd - k;
                    right = i + k;
                }
                if (k != 0)
                    func(next(first, i + isOdd - k), next(first, i + k));
            }
        }
    }

public:
    constexpr string longestPalindrome(const string &str) const noexcept {
        string_view result{};
        const auto func{
            [&result](
                const auto first,
                const auto last
            ) constexpr noexcept -> void {
                if (size_t(distance(first, last)) > size(result))
                    result = string_view(first, last);
            }
        };
        findPalindromes(cbegin(str), cend(str), func);

        return string(result);
    }
};
