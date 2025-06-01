#include <numeric>

using namespace std;

/**
 * [a, ...,                c     d,     f, ...,    b]
 * [false, false, ..., false, true,  true, ..., true]
 * In that example `d` is returned, because:
 * <ul>
 *   <li>{@code predicate(c) = false}
 *   <li>{@code predicate(d) = true}
 *   <li>{@code predicate(f) = true}
 * </ul>
 * @return the first value on which `predicate` returns `true`.
 */
template<typename T, typename Predicate>
static constexpr T binary_search(T a, T b, Predicate predicate) noexcept {
    while (a != b) {
        const T middle{midpoint(a, b)};
        if (predicate(middle))
            b = middle;
        else
            a = middle + 1;
    }
    return a;
}
