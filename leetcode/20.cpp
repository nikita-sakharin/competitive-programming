class Solution final {
private:
    template<class T>
    using Stack = stack<T, vector<T>>;

    static constexpr char getClosing(const char opening) noexcept {
        return char((opening + 1) | 0X1);
    }

public:
    constexpr bool isValid(const string &str) const noexcept {
        Stack<char> lifo{};
        for (const auto ch : str)
            if (ch == '(' || ch == '[' || ch == '{')
                lifo.push(ch);
            else if (!empty(lifo) && getClosing(lifo.top()) == ch)
                lifo.pop();
            else
                return false;

        return empty(lifo);
    }
};
