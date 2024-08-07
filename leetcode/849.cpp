class Solution final {
public:
    constexpr int maxDistToClosest(const vector<int> &seats) const noexcept {
        const auto size{seats.size()};
        auto maxDistance{0UZ}, cnt{0UZ};
        while (maxDistance < size && seats[maxDistance] == 0)
            ++maxDistance;
        for (auto i{maxDistance}; i < size; ++i)
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
