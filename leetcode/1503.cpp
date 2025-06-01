class Solution final {
public:
    constexpr int getLastMoment(
        const int n,
        const vector<int> &left,
        const vector<int> &right
    ) const noexcept {
        auto result{0};
        if (!empty(left))
            result = *max_element(cbegin(left), cend(left));
        if (!empty(right))
            result = max(result, n - *min_element(cbegin(right), cend(right)));
        return result;
    }
};
