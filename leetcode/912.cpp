class Solution final {
private:
    template<class Iter>
    using Difference = iterator_traits<Iter>::difference_type;

    template<class Iter>
    using Value = iterator_traits<Iter>::value_type;

    template<class Iter>
    using Task = tuple<Iter, Iter, Iter>;

    template<class Iter>
    static constexpr auto
        category{typename iterator_traits<Iter>::iterator_category()};

    template<class T>
    static constexpr T midpointFloor(
        const T x,
        const T y
    ) noexcept {
        return (x & y) + ((x ^ y) >> 1);
    }

    template<class Iter>
    static constexpr pair<Iter, Iter> nthElement(
        Iter first1, Difference<Iter> length1,
        const Iter first2, const Difference<Iter> length2,
        Difference<Iter> n
    ) noexcept {
        if (n > length2) {
            first1 += n - length2;
            n = length2;
        }
        if (length1 > n)
            length1 = n;

        while (length1 > 0) {
            const auto index1{(length1 - 1) >> 1}, index2{n - index1 - 1};
            const auto iter1{next(first1, index1)}, iter2{next(first2, index2)};
            if (*iter2 < *iter1)
                length1 = index1;
            else {
                first1 = next(iter1);
                length1 -= index1 + 1;
                n -= index1 + 1;
            }
        }

        return {first1, next(first2, n)};
    }

    template<class Iter>
    static constexpr pair<Iter, Iter> nthElement(
        const Iter first1, const Iter last1,
        const Iter first2, const Iter last2,
        Difference<Iter> n
    ) noexcept {
        const auto
            length1{distance(first1, last1)}, length2{distance(first2, last2)};

        if (n <= 0)
            return {first1, first2};

        if (n - length1 >= length2)
            return {last1, last2};

        if (length1 > length2) {
            const auto [iter1, iter2]{
                nthElement(first2, length2, first1, length1, n)
            };
            return {iter2, iter1};
        }

        return nthElement(first1, length1, first2, length2, n);
    }

    template<class Iter, template<class> class Container = deque>
    class DefaultMerger final {
    private:
        queue<Value<Iter>, Container<Value<Iter>>> fifo{};

        constexpr void operator()(
            Iter first,
            const Iter middle,
            const Iter last,
            const forward_iterator_tag
        ) noexcept {
            if (first == middle || middle == last)
                return;

            auto second{middle};
            auto leftNonEmpty{true};
            do {
                if (leftNonEmpty)
                    fifo.push(move(*first));
                if (empty(fifo) || (second != last && *second < fifo.front())) {
                    *first = move(*second);
                    ++second;
                } else {
                    *first = move(fifo.front());
                    fifo.pop();
                }
                ++first;
                leftNonEmpty = leftNonEmpty && first != middle;
            } while (leftNonEmpty || !empty(fifo));
        }

        constexpr void operator()(
            Iter first,
            const Iter middle,
            const Iter last,
            const random_access_iterator_tag
        ) noexcept {
            if (first == middle || middle == last)
                return;

            auto second{middle};
            do {
                if (first < middle)
                    fifo.push(move(*first));
                if (empty(fifo) || (second != last && *second < fifo.front())) {
                    *first = move(*second);
                    ++second;
                } else {
                    *first = move(fifo.front());
                    fifo.pop();
                }
                ++first;
            } while (first < middle || !empty(fifo));
        }

    public:
        constexpr void operator()(
            Iter first,
            const Iter middle,
            const Iter last
        ) noexcept {
            (*this)(first, middle, last, category<Iter>);
        }
    };

    template<class Iter, template<class> class Container = vector>
    class RotateMerger final {
    private:
        stack<Task<Iter>, Container<Task<Iter>>> lifo{};

    public:
        constexpr void operator()(
            Iter first,
            Iter middle,
            Iter last
        ) noexcept {
            lifo.emplace(first, middle, last);
            do {
                tie(first, middle, last) = lifo.top();
                lifo.pop();
                if (first == middle || middle == last)
                    continue;

                const auto leftSize{distance(first, middle)},
                    rightSize{distance(middle, last)};
                Iter leftIter, rightIter;
                if (leftSize < rightSize) {
                    rightIter = next(middle, (rightSize + 1) >> 1);
                    leftIter = upper_bound(first, middle, *prev(rightIter));
                    middle = prev(rotate(leftIter, middle, rightIter));
                } else {
                    leftIter = next(first, (leftSize - 1) >> 1);
                    rightIter = lower_bound(middle, last, *leftIter);
                    middle = rotate(leftIter, middle, rightIter);
                }

                lifo.emplace(first, leftIter, middle);
                lifo.emplace(next(middle), rightIter, last);
            } while (!empty(lifo));
        }
    };

    template<class Iter, template<class> class Container = vector>
    class RotatePartitionMerger final {
    private:
        stack<Task<Iter>, Container<Task<Iter>>> lifo{};

    public:
        constexpr void operator()(
            Iter first,
            Iter middle,
            Iter last
        ) noexcept {
            lifo.emplace(first, middle, last);
            do {
                tie(first, middle, last) = lifo.top();
                lifo.pop();
                if (first == middle || middle == last)
                    continue;

                const auto n{
                    midpointFloor(distance(first, middle), distance(middle, last))
                };
                const auto [leftIter, rightIter]{
                    nthElement(first, middle, middle, last, n)
                };
                middle = rotate(leftIter, middle, rightIter);

                lifo.emplace(first, leftIter, middle);
                lifo.emplace(middle, rightIter, last);
            } while (!empty(lifo));
        }
    };

    template<class Iter, class Merger>
    static constexpr void mergeSort(
        const Iter first,
        const Iter last,
        Merger &&merger
    ) noexcept {
        const auto length{distance(first, last)}, half{length >> 1};
        Difference<Iter> step{1};
        while (step < length) {
            auto n{length};
            auto iter{first};
            while (n > 0) {
                const auto
                    left{min(step, n)},
                    right{min(step, n - left)};
                const auto middle{next(iter, left)},
                    nextIter{next(middle, right)};
                merger(iter, middle, nextIter);
                n -= left + right;
                iter = nextIter;
            }
            step = step <= half ? step << 1 : length;
        }
    }

    template<class Iter>
    static constexpr void defaultMergeSort(
        const Iter first,
        const Iter last
    ) noexcept {
        mergeSort(first, last, DefaultMerger<Iter>{});
    }

    template<class Iter>
    static constexpr void rotateMergeSort(
        const Iter first,
        const Iter last
    ) noexcept {
        mergeSort(first, last, RotateMerger<Iter>{});
    }

    template<class Iter>
    static constexpr void rotatePartitionMergeSort(
        const Iter first,
        const Iter last
    ) noexcept {
        mergeSort(first, last, RotatePartitionMerger<Iter>{});
    }

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
