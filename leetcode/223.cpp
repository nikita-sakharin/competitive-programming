class Solution final {
private:
    template<class T>
    using Interval = array<T, 2>;

    template<class T>
    using Point = array<T, 2>;

    template<class T>
    using Rect = array<Point<T>, 2>;

    enum Coordinate : size_t {
        X,
        Y
    };

    template<class T>
    static constexpr T area(const Rect<T> &rect) noexcept {
        return (rect[1][X] - rect[0][X]) * (rect[1][Y] - rect[0][Y]);
    }

    template<class T>
    static constexpr T intersection(
        const Interval<T> &a,
        const Interval<T> &b
    ) noexcept {
        return max(T{0}, min(a[1], b[1]) - max(a[0], b[0]));
    }

    template<class T>
    static constexpr T intersectionArea(
        const Rect<T> &rectA,
        const Rect<T> &rectB
    ) noexcept {
        return intersection(interval(rectA, X), interval(rectB, X))
            * intersection(interval(rectA, Y), interval(rectB, Y));
    }

    template<class T>
    static constexpr Interval<T> interval(
        const Rect<T> &rect,
        const Coordinate coord
    ) noexcept {
        return {rect[0][coord], rect[1][coord]};
    }

public:
    constexpr int computeArea(
        const int ax1, const int ay1,
        const int ax2, const int ay2,
        const int bx1, const int by1,
        const int bx2, const int by2
    ) const noexcept {
        const Rect<int>
            rectA{{{ax1, ay1}, {ax2, ay2}}},
            rectB{{{bx1, by1}, {bx2, by2}}};
        return area(rectA) + area(rectB) - intersectionArea(rectA, rectB);
    }
};
