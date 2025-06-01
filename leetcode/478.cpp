class Solution final {
private:
    using dbl = double;

    static inline piecewise_linear_distribution<dbl> radiusDistribution(
        const dbl radius
    ) noexcept {
        const auto i = {0.0, radius}, w = {0.0, 2 / radius};
        return piecewise_linear_distribution(cbegin(i), cend(i), cbegin(w));
    }

    default_random_engine eng{random_device{}()};
    const dbl xCenter{0.0}, yCenter{0.0};
    piecewise_linear_distribution<dbl> rDist;
    uniform_real_distribution<dbl> phiDist{0.0, 2.0 * numbers::pi};

    inline vector<dbl> toCircle(
        const dbl r,
        const dbl phi
    ) const noexcept {
        return {cos(phi) * r + xCenter, sin(phi) * r + yCenter};
    }

public:
    inline Solution(
        const dbl radius,
        const dbl xCenter,
        const dbl yCenter
    ) noexcept : xCenter{xCenter}, yCenter{yCenter},
        rDist{radiusDistribution(radius)} {
    }

    inline vector<dbl> randPoint() noexcept {
        return toCircle(rDist(eng), phiDist(eng));
    }
};
/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(radius, x_center, y_center);
 * vector<double> param_1 = obj->randPoint();
 */
