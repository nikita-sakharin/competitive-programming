class Solution final {
private:
    template<class T>
    static constexpr auto digits10{numeric_limits<T>::digits10};

public:
    constexpr bool isPalindrome(const int x) const noexcept {
        if (x < 0)
            return false;

        array<char, digits10<decltype(x)> + 1> arr{};
        const auto first{data(arr)}, last{to_chars(begin(arr), end(arr), x).ptr};
        return equal(first, midpoint(first, last), reverse_iterator(last));
    }
};
