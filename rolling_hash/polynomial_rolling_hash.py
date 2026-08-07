#!/usr/bin/env python
from bisect import bisect_left
from collections import namedtuple
from collections.abc import Iterator
from functools import cached_property
from itertools import chain
from math import gcd
from unittest import TestCase, main

from mpmath import (
    e, euler, fabs, floor, frac, ldexp, ln, log, nint, phi, pi, power, sqrt,
    workprec,
)
from sympy import (
    factorint, is_primitive_root, isprime, nextprime, prevprime,
    primitive_root, totient,
)

from bijective import to_bijective

def has_primitive_root(n: int, /) -> bool:
    if n < 2:
        raise ValueError(f'{n} < 2')

    factors: dict[int, int] = factorint(n)
    return (
        len(factors) == 1 and factors.get(2, 0) < 3
        or len(factors) == 2 and factors.get(2, 0) == 1
    )


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


def primitive_roots(n: int, /) -> Iterator[int]:
    g: int = primitive_root(n)
    phi: int = int(totient(n))
    for k in range(1, phi):
        if gcd(k, phi) == 1:
            yield pow(g, k, mod=n)


def primitive_roots_sorted(
    n: int,
    /,
    *,
    start: int = 2,
    stop: int | None = None
) -> Iterator[int]:
    if stop is None:
        stop = n

    if not all(map(lambda arg: isinstance(arg, int), (n, start, stop))):
        raise TypeError(', '.join(
            f'type of `{arg}` is `{type(arg)}`'
            for arg in (n, start, stop)
        ))
    if not 2 <= start <= stop <= n or not has_primitive_root(n):
        raise ValueError(
            f'Inequation `2 <= {start} <= {stop} <= {n}` is not satisfied'
            f' or `{n}` has no primitive roots'
        )

    phi: int = int(totient(n))
    factors: dict[int, int] = factorint(phi)
    for g in range(start, stop):
        if all(pow(g, phi // p, mod=n) != 1 for p in factors):
            yield g


class Modulo(namedtuple('Modulo', ['bits', 'offset'])):
    @cached_property
    def mask(self) -> int:
        return (1 << self.bits) - 1

    @cached_property
    def modulo(self) -> int:
        return (1 << self.bits) + self.offset

    def __rmod__(self, number: int, /) -> int:
        if number < 0:
            number = self.modulo - (-number % self)

        while number.bit_length() > self.bits:
            number = (number & self.mask) - (number >> self.bits) * self.offset
        if number < 0:
            number += self.modulo
        if number >= self.modulo:
            number -= self.modulo
        return number


class PolynomialHash(namedtuple(
    'PolynomialHash',
    ['multiplier', 'increment', 'modulus', 'seed', 'bits'],
)):
    @cached_property
    def mask(self) -> int:
        return (1 << self.bits) - 1

    def __call__(self, binary: bytes, /) -> int:
        state: int = self.seed
        for b in chain(binary, (len(binary),)):
            state = (state * self.multiplier + b + self.increment) % self.modulus

        result: int = 0
        while state:
            result ^= state & self.mask
            state >>= self.bits
        return result


class TestPrimitiveRoot(TestCase):
    def test_primitive_roots(self):
        for n, roots in [
            (3, [2]), (5, [2, 3]), (7, [3, 5]), (11, [2, 8, 7, 6]),
            (13, [2, 6, 11, 7]), (17, [3, 10, 5, 11, 14, 7, 12, 6]),
            (19, [2, 13, 14, 15, 3, 10]),
            (23, [5, 10, 20, 17, 11, 21, 19, 15, 7, 14]),
            (29, [2, 8, 3, 19, 18, 14, 27, 21, 26, 10, 11, 15]),
            (31, [3, 17, 13, 24, 22, 12, 11, 21]),
            (37, [2, 32, 17, 13, 15, 18, 35, 5, 20, 24, 22, 19]),
            (41, [6, 11, 29, 19, 28, 24, 26, 34, 35, 30, 12, 22, 13, 17, 15,
                  7]),
            (43, [3, 28, 30, 12, 26, 19, 34, 5, 18, 33, 20, 29]),
            (47, [5, 31, 23, 11, 40, 13, 43, 41, 38, 10, 15, 22, 33, 26, 39,
                  35, 29, 20, 30, 45, 44, 19]),
            (53, [2, 8, 32, 22, 35, 34, 14, 3, 12, 48, 33, 26, 51, 45, 21, 31,
                  18, 19, 39, 50, 41, 5, 20, 27]),
            (59, [2, 8, 32, 10, 40, 42, 50, 23, 33, 14, 56, 47, 11, 44, 55, 43,
                  54, 39, 38, 34, 18, 13, 52, 31, 6, 24, 37, 30]),
            (61, [2, 6, 35, 18, 44, 54, 10, 30, 59, 55, 26, 43, 17, 7, 51, 31])
        ]:
            self.assertEqual(list(primitive_roots(n)), roots)
            self.assertEqual(list(primitive_roots_sorted(n)), sorted(roots))

    def test_has_primitive_roots(self):
        has_root: set[int] = {
            2, 3, 4, 5, 6, 7, 9, 10, 11, 13, 14, 17, 18, 19, 22, 23, 25, 26,
            27, 29, 31, 34, 37, 38, 41, 43, 46, 47, 49, 50, 53, 54, 58, 59, 61,
            62, 67, 71, 73, 74, 79, 81, 82, 83, 86, 89, 94, 97, 98, 101, 103,
            106, 107, 109, 113, 118, 121, 122, 125, 127, 131, 134, 137, 139
        }
        for n in range(-1, max(has_root) + 1):
            if n in range(-2, 2):
                self.assertRaises(ValueError, has_primitive_root, n)
            else:
                self.assertEqual(has_primitive_root(n), n in has_root)


class TestModulo(TestCase):
    def test_rmod(self):
        for modulo in [
            Modulo(bits=64, offset=-1469), Modulo(bits=64, offset=3103)
        ]:
            for point in [
                -(1 << modulo.bits), -modulo.modulo, 0,
                modulo.modulo, 1 << modulo.bits
            ]:
                for delta in range(-4, 4):
                    number: int = point + delta
                    self.assertEqual(number % modulo, number % modulo.modulo)


class TestPolynomialHash(TestCase):
    @staticmethod
    def polynomial_hash(poly_hash: PolynomialHash, binary: bytes) -> int:
        multiplier: int = poly_hash.multiplier
        increment: int = poly_hash.increment
        modulus: int = poly_hash.modulus.modulo

        result: int = poly_hash.seed
        for b in binary:
            result = (result * multiplier + b + increment) % modulus
        result = (result * multiplier + increment) % modulus
        return result & poly_hash.mask

    def test_call(self):
        for modulo in [
            Modulo(bits=64, offset=-1469), Modulo(bits=64, offset=3103)
        ]:
            poly_hash: PolynomialHash = PolynomialHash(
                multiplier=257,
                increment=1,
                modulus=modulo,
                seed=1,
                bits=32
            )
            for binary in [
                B'', B'\x00', B'\x01', B'\xFF',
                B'\x00\x00', B'\x00\x01', B'\x00\xFF',
                B'\x01\x00', B'\x01\x01', B'\x01\xFF',
                B'\xFF\x00', B'\xFF\x01', B'\xFF\xFF',
                B'\x00\x00\x00', B'\x00\x00\x01', B'\x00\x00\xFF',
                B'\x00\x01\x00', B'\x00\x01\x01', B'\x00\x01\xFF',
                B'\x00\xFF\x00', B'\x00\xFF\x01', B'\x00\xFF\xFF',
                B'\x01\x00\x00', B'\x01\x00\x01', B'\x01\x00\xFF',
                B'\x01\x01\x00', B'\x01\x01\x01', B'\x01\x01\xFF',
                B'\x01\xFF\x00', B'\x01\xFF\x01', B'\x01\xFF\xFF',
                B'\xFF\x00\x00', B'\xFF\x00\x01', B'\xFF\x00\xFF',
                B'\xFF\x01\x00', B'\xFF\x01\x01', B'\xFF\x01\xFF',
                B'\xFF\xFF\x00', B'\xFF\xFF\x01', B'\xFF\xFF\xFF',
                B'\x00\x00\x00\x00'
            ]:
                self.assertEqual(
                    poly_hash(binary),
                    self.polynomial_hash(poly_hash, binary)
                )


class TestSafePrime(TestCase):
    def test_safe_prime(self):
        safe_primes: list[int] = [
            5, 7, 11, 23, 47, 59, 83, 107, 167, 179, 227, 263, 347, 359, 383,
            467, 479, 503, 563, 587, 719, 839, 863, 887, 983, 1019, 1187, 1283,
            1307, 1319, 1367, 1439, 1487, 1523, 1619, 1823, 1907, 2027, 2039,
            2063, 2099, 2207, 2447, 2459, 2579, 2819, 2879, 2903, 2963
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
    # main()

    modulo: Modulo = Modulo(bits=256, offset=-36113)
    with workprec(modulo.bits << 1):
        irrationals: list = [
            frac(1 / pi),
            frac(1 / sqrt(2)),
            frac(1 / sqrt(3)),
            frac(1 / sqrt(pi)),
            frac(2 / pi),
            frac(2 / sqrt(pi)),
            frac(e),
            frac(euler),
            frac(ln(2)),
            frac(ln(10)),
            frac(log(e, 2)),
            frac(log(e, 10)),
            frac(phi),
            frac(pi),
            frac(pi / 2),
            frac(pi / 4),
            frac(sqrt(2)),
            frac(sqrt(3)),
        ]
        multipliers: list[int] = [
            int(nint(ldexp(irrational, modulo.bits)))
            for irrational in irrationals
        ]
        multipliers = [
            base
            for base in multipliers
            if is_primitive_root(base, modulo.modulo) and base & 1
        ]
        # min_exp: int = modulo.bits + min(
        #     int(floor(log(irrational, 2)))
        #     for irrational in irrationals
        # )
        # powers: list = [
        #     power(modulo.modulo, exponent / modulo.bits)
        #     for exponent in range(min_exp, modulo.bits + 1)
        # ]
        # multipliers = sorted(
        #     multipliers,
        #     key=lambda b: min(powers, key=lambda p: fabs(b / p - 1))
        # )
        multiplier: int = multipliers[2]
        increment: int = int(nint(ldexp(frac(1 + sqrt(2)), modulo.bits)))
        seed: int = int(nint(ldexp(frac(1.5 + sqrt(13) / 2), modulo.bits)))

    polynomial_hash: PolynomialHash = PolynomialHash(
        multiplier=multiplier,
        increment=increment,
        modulus=modulo,
        seed=seed,
        bits=64,
    )
    for i in range(512):
        h: int = polynomial_hash(to_bijective(i))
        print(f'{h:064b}')
