class Solution final {
private:
    template<class Iter>
    static constexpr auto
        category{typename iterator_traits<Iter>::iterator_category()};

    template<class Iter>
    static constexpr void reverse(
        Iter first,
        Iter last,
        const bidirectional_iterator_tag
    ) noexcept {
        while (first != last && first != --last)
            iter_swap(first++, last);
    }

    template<class Iter>
    static constexpr void reverse(
        Iter first,
        Iter last,
        const random_access_iterator_tag
    ) noexcept {
        while (first < last)
            iter_swap(first++, --last);
    }

    template<class Iter>
    static constexpr void reverse(Iter first, Iter last) noexcept {
        reverse(first, last, category<Iter>);
    }

public:
    constexpr void reverseString(vector<char> &str) const noexcept {
        Solution::reverse(begin(str), end(str));
    }
};
