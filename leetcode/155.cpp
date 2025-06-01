class MinStack final {
private:
    template<class T>
    using Stack = stack<T, vector<T>>;

    Stack<int> valueStack{}, minStack{};

public:
    constexpr void push(const int value) noexcept {
        valueStack.push(value);
        if (empty(minStack) || minStack.top() >= value)
            minStack.push(value);
    }

    constexpr void pop() noexcept {
        if (minStack.top() == valueStack.top())
            minStack.pop();
        valueStack.pop();
    }

    constexpr int top() const noexcept {
        return valueStack.top();
    }

    constexpr int getMin() const noexcept {
        return minStack.top();
    }
};
/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */
