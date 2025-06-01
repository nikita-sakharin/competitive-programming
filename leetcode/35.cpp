class Solution final {
private:
    template<class Iter, class T>
    static constexpr Iter lowerBound(
        Iter first,
        const Iter last,
        const T &value
    ) noexcept {
        auto length{distance(first, last)};
        while (length > 0) {
            const auto half{(length - 1) >> 1};
            const auto middle{next(first, half)};
            if (*middle < value) {
                first = next(middle);
                length -= half + 1;
            } else
                length = half;
        }
        return first;
    }

public:
    constexpr int searchInsert(
        const vector<int> &nums,
        const int target
    ) const noexcept {
        const auto first{cbegin(nums)};
        return int(distance(first, lowerBound(first, cend(nums), target)));
    }
};
