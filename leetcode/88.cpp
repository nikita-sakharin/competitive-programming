class Solution final {
public:
    constexpr void merge(
        vector<int> &values1, ptrdiff_t length1,
        const vector<int> &values2, ptrdiff_t length2
    ) const noexcept {
        --length1, --length2;
        while (length1 >= 0 || length2 >= 0)
            if (length1 < 0
                || (length2 >= 0 && values1[length1] < values2[length2])
            ) {
                values1[length1 + length2 + 1] = values2[length2];
                --length2;
            } else {
                values1[length1 + length2 + 1] = values1[length1];
                --length1;
            }
    }
};
