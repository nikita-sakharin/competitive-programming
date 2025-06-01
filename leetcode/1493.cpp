class Solution final {
private:
    template<class Iter>
    using Difference = iterator_traits<Iter>::difference_type;

    template<class Iter, class T>
    static constexpr pair<Iter, Difference<Iter>> adjacentCount(
        const Iter first,
        const Iter last,
        const T &value
    ) noexcept {
        const auto iter{find(first, last, value)};
        return {iter, distance(first, iter)};
    }

public:
    constexpr int longestSubarray(const vector<int> &nums) const noexcept {
        const auto last{cend(nums)};
        auto [iter, prevCnt] = adjacentCount(cbegin(nums), last, 0);
        auto result{prevCnt - (iter == last)};
        while (iter != last) {
            ptrdiff_t zeroCnt{0}, oneCnt{0};
            tie(iter, zeroCnt) = adjacentCount(iter, last, 1);
            tie(iter, oneCnt) = adjacentCount(iter, last, 0);
            result = max(result, (zeroCnt == 1 ? prevCnt : 0) + oneCnt);
            prevCnt = oneCnt;
        }
        return int(result);
    }
};
