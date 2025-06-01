class Solution final {
public:
    constexpr bool isOneEditDistance(
        const string &s,
        const string &t
    ) const noexcept {
        const auto sLength{size(s)}, tLength{size(t)};
        if (sLength < tLength)
            return isOneEditDistance(t, s);
        if (sLength - tLength > 1)
            return false;

        const auto tLast{cend(t)};
        for (auto sIter{cbegin(s)}, tIter{cbegin(t)}; tIter != tLast; ++sIter, ++tIter)
            if (*sIter != *tIter)
                return equal(
                    next(sIter), cend(s),
                    next(tIter, sLength == tLength), tLast
                );
        return sLength != tLength;
    }
};
