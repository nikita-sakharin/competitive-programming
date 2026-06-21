class Solution final {
private:
    template<class Iter>
    static constexpr void siftDown(
        const Iter first,
        Iter element,
        const Iter last
    ) noexcept {
        const auto half{next(first, distance(first, last) >> 1)};
        while (element < half) {
            auto child{next(element, distance(first, element) + 1)};
            if (const auto sibling{next(child)};
                sibling != last && *child < *sibling
            )
                child = sibling;
            if (*element >= *child)
                break;
            iter_swap(element, child);
            element = child;
        }
    }

    template<class Iter>
    static constexpr void siftUp(const Iter first, Iter element) noexcept {
        while (element != first) {
            const auto
                parent{prev(element, (distance(first, element) >> 1) + 1)};
            if (*parent >= *element)
                break;
            iter_swap(parent, element);
            element = parent;
        }
    }

    template<class Iter>
    static constexpr void popHeap(const Iter first, Iter last) noexcept {
        iter_swap(first, --last);
        siftDown(first, first, last);
    }

    template<class Iter>
    static constexpr void pushHeap(const Iter first, const Iter last) noexcept {
        siftUp(first, prev(last));
    }

    template<class Iter>
    static constexpr void makeHeap(const Iter first, const Iter last) noexcept {
        const auto length{distance(first, last)};
        if (length < 2)
            return;

        auto iter{next(first, length >> 1)};
        do
            siftDown(first, --iter, last);
        while (iter != first);
    }

    template<class Iter>
    static constexpr void sortHeap(const Iter first, Iter last) noexcept {
        if (distance(first, last) < 2)
            return;

        const auto second{next(first)};
        do
            popHeap(first, last);
        while (--last != second);
    }

    template<class Iter>
    static constexpr void heapSort(
        const Iter first,
        const Iter last
    ) noexcept {
        makeHeap(first, last);
        sortHeap(first, last);
    }

public:
    constexpr vector<int> sortArray(vector<int> &nums) const noexcept {
        heapSort(begin(nums), end(nums));
        return move(nums);
    }
};
