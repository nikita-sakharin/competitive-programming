class Solution final {
private:
    template<class Iter, class T>
    static constexpr pair<Iter, Iter> equalRange(
        Iter first,
        const Iter last,
        const T &value
    ) noexcept {
        first = lowerBound(first, last, value);

        return {first, upperBound(first, last, value)};
    }

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

    template<class Iter, class T>
    static constexpr Iter upperBound(
        Iter first,
        const Iter last,
        const T &value
    ) noexcept {
        auto length{distance(first, last)};
        while (length > 0) {
            const auto half{(length - 1) >> 1};
            const auto middle{next(first, half)};
            if (value < *middle)
                length = half;
            else {
                first = next(middle);
                length -= half + 1;
            }
        }

        return first;
    }

public:
    constexpr vector<int> searchRange(
        const vector<int> &nums,
        const int target
    ) const noexcept {
        const auto first{cbegin(nums)}, last{cend(nums)};
        const auto [lower, upper]{equalRange(first, last, target)};

        if (lower == upper)
            return {-1, -1};

        return {int(lower - first), int(upper - first) - 1};
    }
};
