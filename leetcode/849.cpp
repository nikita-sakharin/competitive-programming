class Solution final {
public:
    constexpr int maxDistToClosest(const vector<int> &seats) const noexcept {
        const auto length{size(seats)};
        auto maxDistance{0UZ}, cnt{0UZ};
        while (maxDistance < length && seats[maxDistance] == 0)
            ++maxDistance;
        for (auto i{maxDistance}; i < length; ++i)
            if (seats[i] == 0)
                ++cnt;
            else {
                maxDistance = max(maxDistance, (cnt + 1) >> 1);
                cnt = 0;
            }
        maxDistance = max(maxDistance, cnt);
        return int(maxDistance);
    }
};
