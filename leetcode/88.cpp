class Solution final {
public:
    constexpr void merge(
        vector<int> &values1, ptrdiff_t size1,
        const vector<int> &values2, ptrdiff_t size2
    ) const noexcept {
        --size1, --size2;
        while (size1 >= 0 || size2 >= 0)
            if (size1 < 0 || (size2 >= 0 && values1[size1] < values2[size2])) {
                values1[size1 + size2 + 1] = values2[size2];
                --size2;
            } else {
                values1[size1 + size2 + 1] = values1[size1];
                --size1;
            }
    }
};
