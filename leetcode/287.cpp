class Solution final {
private:
    template<class Iter>
    using Difference = iterator_traits<Iter>::difference_type;

    template<class Iter>
    using Value = iterator_traits<Iter>::value_type;

    template<class T, class Pred>
    static constexpr T binarySearch(T a, T b, Pred &&pred) noexcept {
        while (a != b) {
            const T middle{midpoint(a, b)};
            if (pred(middle))
                b = middle;
            else
                a = middle + 1;
        }

        return a;
    }

    template<class Iter>
    static constexpr Value<Iter> findDuplicateInteger(
        const Iter first,
        const Iter last
    ) noexcept {
        return binarySearch(Difference<Iter>{1}, distance(first, last),
            [first, last](const auto bound) constexpr noexcept -> bool {
                return bound < count_if(first, last,
                    [bound](const auto element) constexpr noexcept -> bool {
                        return element <= bound;
                    }
                );
            }
        );
    }

    template<class Iter>
    static constexpr Value<Iter> findDuplicateInteger(
        const Iter first
    ) noexcept {
        auto slow{*first}, fast{*first};
        do {
            slow = first[Difference<Iter>(slow)];
            fast = first[Difference<Iter>(first[Difference<Iter>(fast)])];
        } while (slow != fast);

        slow = *first;
        while (slow != fast) {
            slow = first[Difference<Iter>(slow)];
            fast = first[Difference<Iter>(fast)];
        }

        return fast;
    }

public:
    constexpr int findDuplicate(const vector<int> &nums) const noexcept {
        return findDuplicateInteger(cbegin(nums));
    }
};
