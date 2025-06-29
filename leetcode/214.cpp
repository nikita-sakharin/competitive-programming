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
                const auto bound{min(i + isOdd, size - i)};
                auto k{i < right
                    ? min(buffer[left + (right - i - 1)], right - i)
                    : isOdd
                };
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
    constexpr string shortestPalindrome(const string &str) const noexcept {
        const auto strFirst{cbegin(str)}, strLast{cend(str)};
        string_view palindrome{};
        findPalindromes(strFirst, strLast,
            [strFirst, &palindrome](
                const auto first,
                const auto last
            ) constexpr noexcept -> void {
                if (first == strFirst && distance(first, last) > ssize(palindrome))
                    palindrome = string_view(first, last);
            }
        );

        const auto strSize{size(str)}, difference{strSize - size(palindrome)};
        string result{};
        result.reserve(difference + strSize);
        const auto iter{back_inserter(result)};
        copy_n(crbegin(str), difference, iter);
        copy(strFirst, strLast, iter);

        return result;
    }
};
