class Solution final {
private:
    template<class InIter, class OutIter, class Pred>
    static constexpr void zFunction(
        const InIter first,
        const InIter last,
        const OutIter outFirst,
        Pred &&whilePred
    ) noexcept {
        using Difference = iterator_traits<InIter>::difference_type;

        const auto length{distance(first, last)};
        for (Difference i{1}, left{0}, right{0}; i < length; ++i) {
            Difference z{0};
            if (i < right)
                z = min(right - i, outFirst[i - left - 1]);

            while (i + z < length && first[z] == first[i + z])
                ++z;
            outFirst[i - 1] = z;
            if (z > 0 && !whilePred(next(first, i), next(first, i + z)))
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
