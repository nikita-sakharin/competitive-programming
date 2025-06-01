class Solution final {
public:
    constexpr vector<vector<int>> merge(
        vector<vector<int>> &intervals
    ) const noexcept {
        const auto last{end(intervals)};
        auto slow{begin(intervals)};
        sort(slow, last);

        for (auto fast{next(slow)}; fast != last; ++fast) {
            auto &slowRight{(*slow)[1]};
            const auto &fastValue{*fast};
            if (slowRight >= fastValue[0])
                slowRight = max(slowRight, fastValue[1]);
            else if (++slow != fast)
                iter_swap(slow, fast);
        }
        intervals.resize(size_t(distance(begin(intervals), slow)) + 1);

        return move(intervals);
    }
};
