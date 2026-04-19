class Solution final {
private:
    template<class Iter, class Pred>
    static constexpr void findPalindromes(
        const Iter first,
        const Iter last,
        Pred &&pred
    ) noexcept {
        using Difference = iterator_traits<Iter>::difference_type;

        if (first == last)
            return;

        const auto length{distance(first, last)};
        vector<Difference> buffer(length);
        for (const auto isOdd : {false, true}) {
            for (Difference i{!isOdd}, left{0}, right{0}; i < length; ++i) {
                const auto border{right - i}, bound{min(i + isOdd, length - i)};
                auto k{border > 0
                    ? min(border, buffer[left + border - 1])
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
                if (k > 0 && pred(next(first, i + isOdd - k), next(first, i + k)))
                    break;
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
            ) constexpr noexcept -> bool {
                if (first == strFirst && distance(first, last) > ssize(palindrome))
                    palindrome = string_view(first, last);

                return false;
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
