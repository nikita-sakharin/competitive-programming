class Solution final {
private:
    template<class InputIter, class T>
    static constexpr pair<InputIter, ptrdiff_t> adjacentCount(
        const InputIter first, const InputIter last,
        const T &value
    ) noexcept {
        const auto iter{find(first, last, value)};
        return {iter, distance(first, iter)};
    }

public:
    constexpr int longestSubarray(const vector<int> &nums) const noexcept {
        const auto numsEnd{nums.cend()};
        auto [iter, lastCnt] = adjacentCount(nums.cbegin(), numsEnd, 0);
        auto result{lastCnt - (iter == numsEnd)};
        while (iter != numsEnd) {
            ptrdiff_t zeroCnt{0}, oneCnt{0};
            tie(iter, zeroCnt) = adjacentCount(iter, numsEnd, 1);
            tie(iter, oneCnt) = adjacentCount(iter, numsEnd, 0);
            result = max(result, zeroCnt == 1 ? lastCnt + oneCnt : oneCnt);
            lastCnt = oneCnt;
        }
        return int(result);
    }
};
