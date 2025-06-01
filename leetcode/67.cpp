class Solution final {
public:
    constexpr string addBinary(string &a, string &b) const noexcept {
        if (size(a) < size(b))
            return addBinary(b, a);

        auto carry{false};
        const auto aLast{crend(a)}, bLast{crend(b)};
        for (auto aIter{rbegin(a)}, bIter{rbegin(b)}; aIter != aLast; ++aIter) {
            const auto
                left{*aIter - '0'},
                right{bIter != bLast ? *bIter++ - '0' : 0},
                sum{carry + left + right};
            *aIter = '0' + (sum & 0X1);
            carry = sum >> 1;
        }
        if (carry)
            a.insert(cbegin(a), '1');

        return move(a);
    }
};
