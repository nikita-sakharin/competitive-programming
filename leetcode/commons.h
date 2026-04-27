#include <assert.h> // assert
#include <limits.h> // LLONG_MAX, LONG_MAX
#include <stdbool.h> // false
#include <stdint.h> // INTMAX_MAX, intmax_t, uintmax_t
#include <stdio.h> // fprintf, perror, stderr
#include <stdlib.h> // exit

#ifndef CHAR_WIDTH
#define CHAR_WIDTH 8
#endif // CHAR_WIDTH

#ifndef SCHAR_WIDTH
#define SCHAR_WIDTH 8
#endif // SCHAR_WIDTH

#ifndef UCHAR_WIDTH
#define UCHAR_WIDTH 8
#endif // UCHAR_WIDTH

#ifndef SHRT_WIDTH
#define SHRT_WIDTH 16
#endif // SHRT_WIDTH

#ifndef USHRT_WIDTH
#define USHRT_WIDTH 16
#endif // USHRT_WIDTH

#ifndef INT_WIDTH
#define INT_WIDTH 32
#endif // INT_WIDTH

#ifndef UINT_WIDTH
#define UINT_WIDTH 32
#endif // UINT_WIDTH

#if LONG_MAX < LLONG_MAX

#ifndef LONG_WIDTH
#define LONG_WIDTH 32
#endif // LONG_WIDTH

#ifndef ULONG_WIDTH
#define ULONG_WIDTH 32
#endif // ULONG_WIDTH

#else // LONG_MAX == LLONG_MAX

#ifndef LONG_WIDTH
#define LONG_WIDTH 64
#endif // LONG_WIDTH

#ifndef ULONG_WIDTH
#define ULONG_WIDTH 64
#endif // ULONG_WIDTH

#endif // LONG_MAX == LLONG_MAX

#ifndef LLONG_WIDTH
#define LLONG_WIDTH 64
#endif // LLONG_WIDTH

#ifndef ULLONG_WIDTH
#define ULLONG_WIDTH 64
#endif // ULLONG_WIDTH

#if LLONG_MAX < INTMAX_MAX

#ifndef INTMAX_WIDTH
#define INTMAX_WIDTH 128
#endif // INTMAX_WIDTH

#ifndef UINTMAX_WIDTH
#define UINTMAX_WIDTH 128
#endif // UINTMAX_WIDTH

#else // LLONG_MAX == INTMAX_MAX

#ifndef INTMAX_WIDTH
#define INTMAX_WIDTH 64
#endif // INTMAX_WIDTH

#ifndef UINTMAX_WIDTH
#define UINTMAX_WIDTH 64
#endif // UINTMAX_WIDTH

#endif // LLONG_MAX == INTMAX_MAX

typedef signed char schar;
typedef unsigned char uchar;
typedef short shrt;
typedef unsigned short ushrt;
typedef unsigned uint;
typedef unsigned long ulong;
typedef long long llong;
typedef unsigned long long ullong;
typedef float flt;
typedef double dbl;
typedef long double ldbl;

#if LLONG_MAX < INTMAX_MAX

#define TYPE_GENERIC_INTEGER(func, expr, ...) _Generic((expr), \
    default: func,                                             \
    uint: u##func,                                             \
    long: l##func,                                             \
    ulong: ul##func,                                           \
    llong: ll##func,                                           \
    ullong: ull##func,                                         \
    intmax_t: imax##func,                                      \
    uintmax_t: umax##func                                      \
)(__VA_ARGS__)

#define TYPE_GENERIC_SIGNED_INTEGER(func, expr, ...) _Generic((expr), \
    default: func,                                                    \
    long: l##func,                                                    \
    llong: ll##func,                                                  \
    intmax_t: imax##func                                              \
)(__VA_ARGS__)

#define TYPE_GENERIC_UNSIGNED_INTEGER(func, expr, ...) _Generic((expr), \
    default: u##func,                                                   \
    ulong: ul##func,                                                    \
    ullong: ull##func,                                                  \
    uintmax_t: umax##func                                               \
)(__VA_ARGS__)

#else // LLONG_MAX == INTMAX_MAX

#define TYPE_GENERIC_INTEGER(func, expr, ...) _Generic((expr), \
    default: func,                                             \
    uint: u##func,                                             \
    long: l##func,                                             \
    ulong: ul##func,                                           \
    llong: ll##func,                                           \
    ullong: ull##func                                          \
)(__VA_ARGS__)

#define TYPE_GENERIC_SIGNED_INTEGER(func, expr, ...) _Generic((expr), \
    default: func,                                                    \
    long: l##func,                                                    \
    llong: ll##func                                                   \
)(__VA_ARGS__)

#define TYPE_GENERIC_UNSIGNED_INTEGER(func, expr, ...) _Generic((expr), \
    default: u##func,                                                   \
    ulong: ul##func,                                                    \
    ullong: ull##func                                                   \
)(__VA_ARGS__)

#endif // LLONG_MAX == INTMAX_MAX

#define TYPE_GENERIC_INTEGER_1(func, x, ...)   \
    TYPE_GENERIC_INTEGER(                      \
        func, (x), x __VA_OPT__(,) __VA_ARGS__ \
    )

#define TYPE_GENERIC_INTEGER_2(func, x, y, ...)         \
    TYPE_GENERIC_INTEGER(                               \
        func, (x) + (y), x, y __VA_OPT__(,) __VA_ARGS__ \
    )

#define TYPE_GENERIC_INTEGER_3(func, x, y, z, ...)               \
    TYPE_GENERIC_INTEGER(                                        \
        func, (x) + (y) + (z), x, y, z __VA_OPT__(,) __VA_ARGS__ \
    )

#define TYPE_GENERIC_INTEGER_4(func, x, y, z, w, ...)                     \
    TYPE_GENERIC_INTEGER(                                                 \
        func, (x) + (y) + (z) + (w), x, y, z, w __VA_OPT__(,) __VA_ARGS__ \
    )

#define TYPE_GENERIC_SIGNED_INTEGER_1(func, x, ...) \
    TYPE_GENERIC_SIGNED_INTEGER(                    \
        func, (x), x __VA_OPT__(,) __VA_ARGS__      \
    )

#define TYPE_GENERIC_SIGNED_INTEGER_2(func, x, y, ...)  \
    TYPE_GENERIC_SIGNED_INTEGER(                        \
        func, (x) + (y), x, y __VA_OPT__(,) __VA_ARGS__ \
    )

#define TYPE_GENERIC_SIGNED_INTEGER_3(func, x, y, z, ...)        \
    TYPE_GENERIC_SIGNED_INTEGER(                                 \
        func, (x) + (y) + (z), x, y, z __VA_OPT__(,) __VA_ARGS__ \
    )

#define TYPE_GENERIC_SIGNED_INTEGER_4(func, x, y, z, w, ...)              \
    TYPE_GENERIC_SIGNED_INTEGER(                                          \
        func, (x) + (y) + (z) + (w), x, y, z, w __VA_OPT__(,) __VA_ARGS__ \
    )

#define TYPE_GENERIC_UNSIGNED_INTEGER_1(func, x, ...) \
    TYPE_GENERIC_UNSIGNED_INTEGER(                    \
        func, (x), x __VA_OPT__(,) __VA_ARGS__        \
    )

#define TYPE_GENERIC_UNSIGNED_INTEGER_2(func, x, y, ...) \
    TYPE_GENERIC_UNSIGNED_INTEGER(                       \
        func, (x) + (y), x, y __VA_OPT__(,) __VA_ARGS__  \
    )

#define TYPE_GENERIC_UNSIGNED_INTEGER_3(func, x, y, z, ...)      \
    TYPE_GENERIC_UNSIGNED_INTEGER(                               \
        func, (x) + (y) + (z), x, y, z __VA_OPT__(,) __VA_ARGS__ \
    )

#define TYPE_GENERIC_UNSIGNED_INTEGER_4(func, x, y, z, w, ...)            \
    TYPE_GENERIC_UNSIGNED_INTEGER(                                        \
        func, (x) + (y) + (z) + (w), x, y, z, w __VA_OPT__(,) __VA_ARGS__ \
    )

#define MAX(x, y) ((x) < (y) ? (y) : (x))
#define MIN(x, y) ((x) > (y) ? (y) : (x))

static inline uint ubitWidth(register const uint value) {
    if (value == 0U)
        return 0U;

    return (uint) (UINT_WIDTH - __builtin_clz(value));
}

static inline uint ulbitWidth(register const ulong value) {
    if (value == 0UL)
        return 0U;

    return (uint) (ULONG_WIDTH - __builtin_clzl(value));
}

static inline uint ullbitWidth(register const ullong value) {
    if (value == 0ULL)
        return 0U;

    return (uint) (ULLONG_WIDTH - __builtin_clzll(value));
}

static inline uint umaxbitWidth(register const uintmax_t value) {
    if (value == UINTMAX_C(0))
        return 0U;

    return (uint) (UINTMAX_WIDTH - __builtin_clzg(value));
}

#define bitWidth(x) TYPE_GENERIC_UNSIGNED_INTEGER_1(bitWidth, x)

static inline bool isSameSign(register const int x, register const int y) {
    return (x ^ y) >= 0;
}

static inline bool lisSameSign(register const long x, register const long y) {
    return (x ^ y) >= 0L;
}

static inline bool llisSameSign(
    register const llong x,
    register const llong y
) {
    return (x ^ y) >= 0LL;
}

static inline bool imaxisSameSign(
    register const intmax_t x,
    register const intmax_t y
) {
    return (x ^ y) >= INTMAX_C(0);
}

#define isSameSign(x, y) TYPE_GENERIC_SIGNED_INTEGER_2(isSameSign, x, y)

static inline int ceilDiv(register const int x, register const int y) {
    assert(y != 0);
    return x / y + (isSameSign(x, y) && x % y != 0);
}

static inline uint uceilDiv(register const uint x, register const uint y) {
    assert(y != 0U);
    return x / y + (x % y != 0U);
}

static inline long lceilDiv(register const long x, register const long y) {
    assert(y != 0L);
    return x / y + (isSameSign(x, y) && x % y != 0L);
}

static inline ulong ulceilDiv(register const ulong x, register const ulong y) {
    assert(y != 0UL);
    return x / y + (x % y != 0UL);
}

static inline llong llceilDiv(
    register const llong x,
    register const llong y
) {
    assert(y != 0LL);
    return x / y + (isSameSign(x, y) && x % y != 0LL);
}

static inline ullong ullceilDiv(
    register const ullong x,
    register const ullong y
) {
    assert(y != 0ULL);
    return x / y + (x % y != 0ULL);
}

static inline intmax_t imaxceilDiv(
    register const intmax_t x,
    register const intmax_t y
) {
    assert(y != INTMAX_C(0));
    return x / y + (isSameSign(x, y) && x % y != INTMAX_C(0));
}

static inline uintmax_t umaxceilDiv(
    register const uintmax_t x,
    register const uintmax_t y
) {
    assert(y != UINTMAX_C(0));
    return x / y + (x % y != UINTMAX_C(0));
}

#define ceilDiv(x, y) TYPE_GENERIC_INTEGER_2(ceilDiv, x, y)

static inline int min(register const int x, register const int y) {
    return MIN(x, y);
}

static inline uint umin(register const uint x, register const uint y) {
    return MIN(x, y);
}

static inline long lmin(register const long x, register const long y) {
    return MIN(x, y);
}

static inline ulong ulmin(register const ulong x, register const ulong y) {
    return MIN(x, y);
}

static inline llong llmin(register const llong x, register const llong y) {
    return MIN(x, y);
}

static inline ullong ullmin(register const ullong x, register const ullong y) {
    return MIN(x, y);
}

static inline intmax_t imaxmin(
    register const intmax_t x,
    register const intmax_t y
) {
    return MIN(x, y);
}

static inline uintmax_t umaxmin(
    register const uintmax_t x,
    register const uintmax_t y
) {
    return MIN(x, y);
}

#define min(x, y) TYPE_GENERIC_INTEGER_2(min, x, y)

static inline int max(register const int x, register const int y) {
    return MAX(x, y);
}

static inline uint umax(register const uint x, register const uint y) {
    return MAX(x, y);
}

static inline long lmax(register const long x, register const long y) {
    return MAX(x, y);
}

static inline ulong ulmax(register const ulong x, register const ulong y) {
    return MAX(x, y);
}

static inline llong llmax(register const llong x, register const llong y) {
    return MAX(x, y);
}

static inline ullong ullmax(register const ullong x, register const ullong y) {
    return MAX(x, y);
}

static inline intmax_t imaxmax(
    register const intmax_t x,
    register const intmax_t y
) {
    return MAX(x, y);
}

static inline uintmax_t umaxmax(
    register const uintmax_t x,
    register const uintmax_t y
) {
    return MAX(x, y);
}

#define max(x, y) TYPE_GENERIC_INTEGER_2(max, x, y)

#define EXIT_IF(condition, message)                         \
    do {                                                    \
        if ((condition)) {                                  \
            fprintf(stderr, "%s:%d: ", __FILE__, __LINE__); \
            perror((message));                              \
            exit(EXIT_FAILURE);                             \
        }                                                   \
    } while (false)

static inline uint nprocessorsConf(void) {
    register const long value = sysconf(_SC_NPROCESSORS_CONF);
    // assert((ulong) value <= UINT_MAX);
    assert(value == -1L || (value >= 0L && (ulong) value <= UINT_MAX));
    return value < 0 ? 0U : (uint) value;
}
