class FirstUnique final {
private:
    using ConstIterator = list<int>::const_iterator;

    list<int> unique{};
    unordered_map<int, ConstIterator> dict{};

public:
    constexpr FirstUnique(const vector<int> &nums) noexcept {
        for (const auto num : nums)
            add(num);
    }

    constexpr int showFirstUnique() const noexcept {
        return empty(unique) ? -1 : unique.front();
    }

    constexpr void add(const int value) noexcept {
        const auto uniqueLast{cend(unique)};
        const auto [iter, inserted](dict.try_emplace(value, uniqueLast));
        if (inserted) {
            unique.push_back(value);
            --iter->second;
        } else if (iter->second != uniqueLast) {
            unique.erase(iter->second);
            iter->second = uniqueLast;
        }
    }
};
/**
 * Your FirstUnique object will be instantiated and called as such:
 * FirstUnique* firstUnique = new FirstUnique(nums);
 * int ans = firstUnique->showFirstUnique();
 * firstUnique->add(value);
 */
