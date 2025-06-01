class Solution final {
private:
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
    constexpr char nextGreatestLetter(
        const vector<char> &letters,
        const char target
    ) const noexcept {
        if (letters.back() <= target)
            return letters.front();

        return *upperBound(cbegin(letters), prev(cend(letters)), target);
    }
};
