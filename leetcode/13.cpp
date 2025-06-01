class Solution final {
private:
    static constexpr int numeralValue(const char numeral) noexcept {
        switch (numeral) {
            case 'I':
                return 1;
            case 'V':
                return 5;
            case 'X':
                return 10;
            case 'L':
                return 50;
            case 'C':
                return 100;
            case 'D':
                return 500;
            case 'M':
                return 1000;
            default:
                unreachable();
        }
    }

public:
    constexpr int romanToInt(const string &str) const noexcept {
        auto result{0}, prevValue{0};
        for (auto i{ssize(str) - 1}; i >= 0; --i) {
            const auto value{numeralValue(str[size_t(i)])};
            if (value < prevValue)
                result -= value;
            else
                result += value;
            prevValue = value;
        }

        return result;
    }
};
