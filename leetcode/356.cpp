class Solution final {
private:
    static constexpr auto dims{2UZ};

    struct Hash final {
    private:
        template<class T>
        static constexpr auto digits{numeric_limits<T>::digits};

        static constexpr auto
            shift{min(digits<int> + 1, digits<intmax_t> - digits<int>)};
        static constexpr hash<intmax_t> hashCode{};

    public:
        constexpr size_t operator()(const array<int, dims> &key) const noexcept {
            return hashCode(intmax_t{key[0]} << shift ^ key[1]);
        }
    };

    template<class T>
    static constexpr auto maxV{numeric_limits<T>::max()};

    template<class T>
    static constexpr auto minV{numeric_limits<T>::min()};

public:
    constexpr bool isReflected(
        const vector<vector<int>> &points
    ) const noexcept {
        auto minX{maxV<int>}, maxX{minV<int>};
        unordered_set<array<int, dims>, Hash> pointSet{};
        for (const auto &point : points) {
            const auto x{point[0]};
            minX = min(minX, x);
            maxX = max(maxX, x);
            pointSet.insert({x, point[1]});
        }

        const auto doubleMiddle{minX + maxX};
        for (const auto &point : points)
            if (!pointSet.contains({doubleMiddle - point[0], point[1]}))
                return false;

        return true;
    }
};
