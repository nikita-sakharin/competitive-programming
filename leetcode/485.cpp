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
    constexpr int findMaxConsecutiveOnes(
        const vector<int> &nums
    ) const noexcept {
        const auto last{cend(nums)};
        auto iter{cbegin(nums)};
        ptrdiff_t result{0};
        while (iter != last) {
            ptrdiff_t oneCnt{0};
            tie(iter, ignore) = adjacentCount(iter, last, 1);
            tie(iter, oneCnt) = adjacentCount(iter, last, 0);
            result = max(result, oneCnt);
        }
        return int(result);
    }
};
