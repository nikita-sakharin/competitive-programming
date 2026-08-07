#!/usr/bin/env python
from bisect import bisect_left
from unittest import TestCase, main

from sympy import isprime, nextprime, prevprime

__all__: list[str] = [
    "is_safe_prime",
    "next_safe_prime",
    "prev_safe_prime",
]


def is_safe_prime(n: int, /) -> bool:
    return isprime(n >> 1) and isprime(n)


def next_safe_prime(n: int, /) -> int:
    while True:
        n = nextprime(n)
        if is_safe_prime(n):
            break
    return n


def prev_safe_prime(n: int, /) -> int:
    while True:
        n = prevprime(n)
        if is_safe_prime(n):
            break
    return n


class TestSafePrime(TestCase):
    def test_safe_prime(self):
        safe_primes: list[int] = [
            5, 7, 11, 23, 47, 59, 83, 107, 167, 179, 227, 263, 347, 359, 383,
            467, 479, 503, 563, 587, 719, 839, 863, 887, 983, 1019, 1187, 1283,
            1307, 1319, 1367, 1439, 1487, 1523, 1619, 1823, 1907, 2027, 2039,
            2063, 2099, 2207, 2447, 2459, 2579, 2819, 2879, 2903, 2963,
        ]
        for n in range(safe_primes[-1]):
            index: int = bisect_left(safe_primes, n)
            is_equal: bool = n == safe_primes[index]
            self.assertEqual(is_safe_prime(n), is_equal)
            self.assertEqual(next_safe_prime(n), safe_primes[index + is_equal])
            if n <= safe_primes[0]:
                self.assertRaises(ValueError, prev_safe_prime, n)
            else:
                self.assertEqual(prev_safe_prime(n), safe_primes[index - 1])


if __name__ == "__main__":
    main()
