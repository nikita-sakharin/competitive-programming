class Solution final {
private:
    template<class InIter, class OutIter, class Pred>
    static constexpr void zFunction(
        const InIter first,
        const InIter last,
        const OutIter outFirst,
        Pred &&pred
    ) noexcept {
        using Difference = iterator_traits<InIter>::difference_type;

        const auto length{distance(first, last)};
        for (Difference i{1}, left{0}, right{0}; i < length; ++i) {
            Difference z{clamp(right - i, 0Z, outFirst[i - left - 1])};
            while (i + z < length && first[z] == first[i + z])
                ++z;
            outFirst[i - 1] = z;
            if (z > 0 && pred(next(first, i), next(first, i + z)))
                break;
            if (i + z > right) {
                left = i;
                right = i + z;
            }
        }
    }

public:
    constexpr int strStr(
        const string &haystack,
        const string &needle
    ) const noexcept {
        const auto needleSize{size(needle)},
            strSize{needleSize + 1 + size(haystack)};
        string str{};
        str.reserve(strSize);
        auto iter{back_inserter(str)};
        copy(cbegin(needle), cend(needle), iter);
        str.push_back('\0');
        copy(cbegin(haystack), cend(haystack), iter);
        vector<ptrdiff_t> z(strSize - 1);
        ptrdiff_t result{-1};

        zFunction(cbegin(str), cend(str), begin(z),
            [needleSize, haystackFirst{cbegin(str) + needleSize + 1}, &result](
                const auto first,
                const auto last
            ) constexpr noexcept -> bool {
                if (distance(first, last) >= ptrdiff_t(needleSize)) {
                    result = distance(haystackFirst, first);
                    return true;
                }

                return false;
            }
        );

        return int(result);
    }
};
/*
template<size_t N, size_t... Indices>
requires(N >= 1)
struct A110654 : public A110654<N - 1, N - 2, N - 1, Indices...> {};

template<size_t... Indices>
struct A110654<1, Indices...> : public index_sequence<Indices...> {};

template<size_t... Indices>
void printSequence(index_sequence<Indices...> seq) {
    cout << "The sequence of size " << size(seq) << ": ";
    ((cout << Indices << ' '), ...);
    cout << '\n';
}
printSequence(A110654<2>{});
printSequence(A110654<3>{});

class Solution final {
private:
    template<class Iter1, class Iter2>
    class ConcatIter final {
    private:
        template<class Iter>
        using Value = iterator_traits<Iter>::value_type;

        variant<Iter1, Iter2> iter{};
        const Iter1 last1{};
        const Iter2 first2{};

        static_assert(
            is_same_v<Value<Iter1>, Value<Iter2>>,
            "is_same_v<iterator_traits<Iter1>::value_type, iterator_traits<Iter2>::value_type> must be true",
            "type iterator_traits<Iter1>::value_type must be the same as iterator_traits<Iter2>::value_type"
        );

    public:
        constexpr ConcatIter(
            const Iter1 iter,
            const Iter1 last1,
            const Iter2 first2
        ) noexcept {
            if (iter == last1)
                iter = first2;
        }

        constexpr ConcatIter<Iter1, Iter2> &operator++() noexcept {
            visit(
                [](auto &iter) constexpr noexcept -> void {
                    ++iter;
                    if (iter == last1)
                        iter = first2;
                },
                iter
            );
            return *this;
        }

        friend constexpr bool operator==(
            const ConcatIter<Iter1, Iter2> lhs,
            const ConcatIter<Iter1, Iter2> rhs
        ) noexcept {
            return lhs.iter == rhs.iter
                && lhs.last1 == rhs.last1 && lhs.first2 == rhs.first2;
        }

        constexpr Value<Iter1> &operator*() const noexcept {
            return visit(
                [](const auto iter) constexpr noexcept -> Value<Iter1> & {
                    return *iter;
                },
                iter
            );
        }
    };

    template<class Iter1, class Iter2>
    static constexpr pair<ConcatIter<Iter1, Iter2>, ConcatIter<Iter1, Iter2>> concat(
        const Iter1 first1, const Iter1 last1,
        const Iter2 first2, const Iter2 last2
    ) noexcept {
        return {ConcatIter{first1}, ConcatIter{last2}};
    }

    // TODO: make `outFirst` one element smaller
    template<class InIter, class OutIter>
    static constexpr void zFunction(
        const InIter first,
        const InIter last,
        const OutIter outFirst
    ) noexcept {
        using Difference = iterator_traits<InIter>::difference_type;

        const auto length{distance(first, last)};
        *outFirst = length;

        for (Difference i{1}, left{0}, right{0}; i < length; ++i) {
            Difference z{0};
            if (i < right)
                z = min(right - i, outFirst[i - left]);

            while (i + z < length && first[z] == first[i + z])
                ++z;
            outFirst[i] = z;

            if (i + z > right) {
                left = i;
                right = i + z;
            }
        }
    }

public:
    constexpr int strStr(
        const string &haystack,
        const string &needle
    ) const noexcept {
        const auto needleSize{size(needle)},
            strSize{needleSize + 1 + size(haystack)};
        string str{};
        str.reserve(strSize);
        auto iter{back_inserter(str)};
        copy(cbegin(needle), cend(needle), iter);
        str.push_back('\0');
        copy(cbegin(haystack), cend(haystack), iter);
        vector<ptrdiff_t> z(strSize);
        zFunction(cbegin(str), cend(str), begin(z));

        for (auto i{needleSize + 1}; i < strSize; ++i)
            if (z[i] >= needleSize)
                return int(i - needleSize - 1);

        return -1;
    }
};
*/
