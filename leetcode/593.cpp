class Solution final {
private:
    using uint = unsigned;

    static constexpr uint distanceSquare(
        const vector<int> &p1,
        const vector<int> &p2
    ) noexcept {
        const auto dx{p1[0] - p2[0]}, dy{p1[1] - p2[1]};
        return uint(dx * dx + dy * dy);
    }

public:
    inline bool validSquare(
        const vector<int> &p1,
        const vector<int> &p2,
        const vector<int> &p3,
        const vector<int> &p4
    ) const noexcept {
        set<uint> distances{};
        distances.insert(distanceSquare(p1, p2));
        distances.insert(distanceSquare(p1, p3));
        distances.insert(distanceSquare(p1, p4));
        distances.insert(distanceSquare(p2, p3));
        distances.insert(distanceSquare(p2, p4));
        distances.insert(distanceSquare(p3, p4));
        return !distances.contains(0) && size(distances) == 2;
    }
};
