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
                auto k{i >= right
                    ? isOdd
                    : min(buffer[left + (right - i - 1)], right - i)
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
        const auto func{
            [strFirst, &palindrome](
                const auto first,
                const auto last
            ) constexpr noexcept -> void {
                if (first == strFirst && distance(first, last) > ssize(palindrome))
                    palindrome = string_view(first, last);
            }
        };
        findPalindromes(strFirst, strLast, func);

        const auto strSize{ssize(str)}, difference{strSize - ssize(palindrome)};
        string result{};
        result.reserve(difference + strSize);
        const auto iter{back_inserter(result)};
        copy(crbegin(str), next(crbegin(str), difference), iter);
        copy(cbegin(str), cend(str), iter);

        return result;
    }
};
