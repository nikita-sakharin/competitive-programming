class MaxStack final {
private:
    template<class T>
    using Stack = stack<T, vector<T>>;

    using ConstIterator = list<int>::const_iterator;

    list<int> values{};
    map<int, Stack<ConstIterator>> dict{};

public:
    constexpr void push(const int value) noexcept {
        values.push_back(value);
        dict[value].push(--cend(values));
    }

    constexpr int pop() noexcept {
        const auto value{values.back()};
        const auto iter{dict.find(value)};
        auto &iterStack{iter->second};
        values.pop_back();
        iterStack.pop();
        if (empty(iterStack))
            dict.erase(iter);

        return value;
    }

    constexpr int top() const noexcept {
        return values.back();
    }

    constexpr int peekMax() const noexcept {
        return (--cend(dict))->first;
    }

    constexpr int popMax() noexcept {
        const auto iter{--end(dict)};
        const auto value{iter->first};
        auto &iterStack{iter->second};
        values.erase(iterStack.top());
        iterStack.pop();
        if (empty(iterStack))
            dict.erase(iter);

        return value;
    }
};
