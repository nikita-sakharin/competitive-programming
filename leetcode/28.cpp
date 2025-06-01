class Solution final {
private:
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
