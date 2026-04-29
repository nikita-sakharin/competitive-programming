#include <stdatomic.h>
#include <stddef.h> // size_t
#include <stdio.h> // printf
#include <stdlib.h> // calloc, free, malloc

#include <pthread.h>

#include "commons.h"

static inline uint base17Prime13Naive(
    register const uchar * restrict ptr,
    register const size_t length
) {
    register const uint hexMask = 0XFU, hexShift = 4U,
        base = 17U, modulo = (1U << 13U) - 1U;
    register uint result = 0U;
    for (register const uchar * const end = ptr + length; ptr < end; ++ptr) {
        result = result * base + (*ptr & hexMask);
        result = result * base + (*ptr >> hexShift & hexMask);
        result %= modulo;
    }

    return result;
}

static inline uint base17Prime13(
    register const uchar * restrict ptr,
    register const size_t length
) {
    register const uint hexMask = 0XFU, hexShift = 4U,
        base = 17U, p = 13U, modulo = (1U << p) - 1U;
    register uint result = 0U;
    for (register const uchar * const end = ptr + length; ptr < end; ++ptr) {
        result = result * base + (*ptr & hexMask);
        result = result * base + (*ptr >> hexShift & hexMask);
        if (result > modulo)
            result = (result >> p) + (result & modulo);
        assert(result <= modulo);
    }

    return result == modulo ? 0U : result;
}

int main(const int argc, char ** const argv) {
    EXIT_IF(argc != 2, "argc != 2");

    ullong limit;
    EXIT_IF(sscanf(argv[1], "%llu", &limit) != 1, "sscanf");

    for (register ullong i = 0ULL; i < limit; ++i) {
        ;
    }

    return 0;
}
