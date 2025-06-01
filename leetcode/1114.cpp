class Foo final {
private:
    using uint = unsigned;

    template<class Integer>
    class Linearizer final {
    private:
        condition_variable condvar{};
        mutex sync{};
        Integer counter{0};

    public:
        template<class Func>
        inline void operator()(
            const Integer index,
            Func &&func
        ) noexcept {
            unique_lock lock{sync};
            condvar.wait(lock, [this, index]() constexpr noexcept -> bool {
                return counter == index;
            });
            func();
            ++counter;
            condvar.notify_all();
        }
    };

    Linearizer<uint> linearizer{};

public:
    inline void first(const function<void()> &printFirst) noexcept {
        linearizer(0, printFirst);
    }

    inline void second(const function<void()> &printSecond) noexcept {
        linearizer(1, printSecond);
    }

    inline void third(const function<void()> &printThird) noexcept {
        linearizer(2, printThird);
    }
};
