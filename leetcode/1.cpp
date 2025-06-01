class Solution final {
public:
    constexpr vector<int> twoSum(
        const vector<int> &values,
        const int target
    ) const noexcept {
        const auto length{size(values)};
        unordered_map<int, size_t> dict{};
        const auto last{cend(dict)};

        for (auto i{0UZ}; i < length; ++i) {
            if (const auto iter{dict.find(target - values[i])}; iter != last)
                return {int(iter->second), int(i)};

            dict[values[i]] = i;
        }

        return {};
    }
};
