class Solution final {
private:
    template<class Container>
    using Key = Container::key_type;

    template<class Container>
    using Mapped = Container::mapped_type;

    template<class Iter>
    using Difference = iterator_traits<Iter>::difference_type;

    template<class Iter>
    using Value = iterator_traits<Iter>::value_type;

    template<class Container>
    static constexpr Mapped<Container> getOrDefault(
        const Container &container,
        const Key<Container> &key,
        const Mapped<Container> &mapped
    ) noexcept {
        if (const auto iter{container.find(key)}; iter != cend(container))
            return iter->second;

        return mapped;
    }

    template<class Iter, class T = Value<Iter>>
    static constexpr Difference<Iter> subrangeSumCountFind(
        Iter first,
        const Iter last,
        const T value
    ) noexcept {
        unordered_map<T, Difference<Iter>> dict{};
        Difference<Iter> result{0};
        for (T prefixSum{0}; first != last; ++first) {
            ++dict[prefixSum];
            prefixSum += *first;
            result += getOrDefault(dict, prefixSum - value, T{0});
        }

        return result;
    }

public:
    constexpr int subarraySum(
        const vector<int> &values,
        const int target
    ) const noexcept {
        return int(subrangeSumCountFind(cbegin(values), cend(values), target));
    }
};
