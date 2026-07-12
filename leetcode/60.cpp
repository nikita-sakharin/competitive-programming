class Solution final {
private:
    template<class T>
    using Stack = stack<T, vector<T>>;

    template<class Iter>
    static constexpr void lexicographic_permutation(
        const Iter first,
        const Iter last,
        const intmax_t index
    ) noexcept {
        if (index < 0)
            lexicographic_permutation(
                make_reverse_iterator(first),
                make_reverse_iterator(last),
                uintmax_t(~index)
            );
        else
            lexicographic_permutation(first, last, uintmax_t(index));
    }

    template<class Iter>
    static constexpr void lexicographic_permutation(
        const Iter first,
        const Iter last,
        uintmax_t index
    ) noexcept {
        const auto length{distance(first, last)};
        Stack<size_t> representation{};
        for (auto i{0UZ}; i < length; ++i) {
            const auto denom{uintmax_t(i + 1)};
            representation.push(size_t(index % denom));
            index /= denom;
        }

        while (!empty(representation)) {
            const auto i{representation.top()}, j{size(representation)};
            representation.pop();

            const auto iIter{next(first, i)}, jIter{next(iIter, j - i)};
            rotate(iIter, next(iIter), jIter);
        }

        reverse(first, last);
    }

public:
    constexpr string getPermutation(
        const int n,
        const int k
    ) const noexcept {
        string elements(size_t(n), '\0');
        const auto first{begin(elements)}, last{end(elements)};
        iota(first, last, '1');
        lexicographic_permutation(first, last, intmax_t(k - 1));

        return elements;
    }
};
