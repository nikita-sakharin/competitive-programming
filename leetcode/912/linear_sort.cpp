class Solution final {
private:
    template<class T>
    static constexpr auto isSigned{numeric_limits<T>::is_signed};

    template<class T>
    static constexpr auto width{isSigned<T> + numeric_limits<T>::digits};

    template<class T>
    static constexpr T ceilDiv(const T x, const T y) noexcept {
        return x / y + (isSameSign(x, y) && x % y != T{0});
    }

    template<class T>
    static constexpr bool isOdd(const T value) noexcept {
        return bool(value & T{1});
    }

    template<class T>
    static constexpr T isSameSign(const T x, const T y) noexcept {
        return (x ^ y) >= T{0};
    }

    enum class RadixSortResult : bool {
        IN_INPUT = false,
        IN_OUTPUT = true
    };

    template<class Allocator = allocator<size_t>>
    class CountingSorter final {
    private:
        vector<size_t, Allocator> count{};

    public:
        constexpr size_t capacity() const noexcept {
            return count.capacity();
        }

        template<class InIter, class OutIter, class Ordinalizer>
        constexpr void operator()(
            const InIter inFirst,
            const InIter inLast,
            const OutIter outFirst,
            const Ordinalizer &ordinalizer
        ) noexcept {
            using Difference = iterator_traits<InIter>::difference_type;

            const auto cardinality{ordinalizer.cardinality()};
            count.resize(cardinality);
            const auto countFirst{begin(count)}, countLast{end(count)};

            fill(countFirst, countLast, 0UZ);

            for_each(inFirst, inLast,
                [this, &ordinalizer](
                    const auto &value
                ) constexpr noexcept -> void {
                    const auto idx{ordinalizer(value)};
                    ++count[idx];
                }
            );

            inclusive_scan(countFirst, countLast, countFirst);

            for_each(
                make_reverse_iterator(inLast),
                make_reverse_iterator(inFirst),
                [this, outFirst, &ordinalizer](
                    auto &value
                ) constexpr noexcept -> void {
                    const auto idx{ordinalizer(value)};
                    const auto pos{--count[idx]};
                    outFirst[Difference(pos)] = move(value);
                }
            );
        }

        constexpr void reserve(const size_t newCapacity) noexcept {
            count.reserve(newCapacity);
        }

        constexpr void shrink_to_fit() noexcept {
            count.shrink_to_fit();
        }
    };

    template<class T>
    class IntegralDigitizer final {
    private:
        size_t bitsM{width<T>};

    public:
        using ValueType = T;

        constexpr IntegralDigitizer() noexcept = default;

        constexpr explicit IntegralDigitizer(
            const size_t bits
        ) noexcept : bitsM{bits} {}

        constexpr size_t operator()(
            const ValueType value,
            const size_t idx,
            const size_t step
        ) const noexcept {
            const auto result{
                size_t(value >> idx & ((ValueType{1} << step) - ValueType{1}))
            };
            if constexpr (isSigned<ValueType>)
                if (idx + step >= bitsM)
                    return result ^ size_t(ValueType{1} << (step - 1));

            return result;
        }

        constexpr size_t bits() const noexcept {
            return bitsM;
        }
    };

    template<class Digitizer>
    class Ordinalizer final {
    private:
        const size_t idxM, stepM;
        const Digitizer &digitizerM;

    public:
        using ValueType = Digitizer::ValueType;

        constexpr Ordinalizer(
            const size_t idx,
            const size_t step,
            const Digitizer &digitizer
        ) noexcept : idxM{idx}, stepM{step}, digitizerM{digitizer} {}

        constexpr size_t operator()(const ValueType &value) const noexcept {
            return digitizerM(value, idxM, stepM);
        }

        constexpr size_t cardinality() const noexcept {
            return 1UZ << stepM;
        }
    };

    template<
        class InIter,
        class OutIter,
        class Digitizer,
        class Sorter = CountingSorter<>
    >
    static constexpr RadixSortResult radixSort(
        const InIter inFirst,
        const InIter inLast,
        const OutIter outFirst,
        const size_t maxStep,
        const Digitizer &digitizer,
        Sorter &&sorter = Sorter{}
    ) noexcept {
        using enum RadixSortResult;

        const auto length{distance(inFirst, inLast)};
        const auto outLast{next(outFirst, length)};
        const auto bits{digitizer.bits()};

        auto idx{0UZ};
        while (idx < bits) {
            const auto step{min(maxStep, bits - idx)};
            const Ordinalizer<Digitizer> ordinalizer{idx, step, digitizer};

            if (isOdd(idx / maxStep))
                sorter(outFirst, outLast, inFirst, ordinalizer);
            else
                sorter(inFirst, inLast, outFirst, ordinalizer);

            idx += step;
        }

        return RadixSortResult{isOdd(ceilDiv(bits, maxStep))};
    }

public:
    constexpr vector<int> sortArray(vector<int> &nums) const noexcept {
        using enum RadixSortResult;

        vector<int> buffer(size(nums));
        const auto result{radixSort(
            begin(nums),
            end(nums),
            begin(buffer),
            9,
            IntegralDigitizer<int>{17}
        )};
        if (result == IN_OUTPUT)
            swap(nums, buffer);

        return move(nums);
    }
};
