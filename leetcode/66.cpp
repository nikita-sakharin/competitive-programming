class Solution final {
private:
    static constexpr auto radix{10};

public:
    constexpr vector<int> plusOne(vector<int> &digits) const noexcept {
        auto carry{true};
        for (auto i{ssize(digits) - 1}; i >= 0 && carry; --i)
            if (++digits[i] < radix)
                carry = false;
            else {
                carry = true;
                digits[i] = 0;
            }
        if (carry)
            digits.insert(cbegin(digits), 1);
        return move(digits);
    }
};
