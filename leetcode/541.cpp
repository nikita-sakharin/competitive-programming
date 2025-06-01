class Solution final {
public:
    constexpr string reverseStr(string &str, const int k) const noexcept {
        const auto last{end(str)};
        auto iter{begin(str)};
        while (iter != last) {
            const auto
                nextIter{next(iter, min(distance(iter, last), ptrdiff_t(k)))};
            reverse(iter, nextIter);
            iter = next(nextIter, min(distance(nextIter, last), ptrdiff_t(k)));
        }
        return move(str);
    }
};
