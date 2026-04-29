#!/usr/bin/env python
from collections import namedtuple
from collections.abc import Iterator
from functools import cached_property
from math import gcd
from unittest import main, TestCase

from sympy import factorint, isprime


def primitive_root(n: int, /) -> int:
    return next(primitive_roots_sorted(n))


def primitive_roots(n: int, /) -> Iterator[int]:
    g: int = primitive_root(n)
    phi: int = n - 1
    for k in range(1, phi):
        if gcd(k, phi) == 1:
            yield pow(g, k, n)


def primitive_roots_sorted(n: int, /) -> Iterator[int]:
    if not isinstance(n, int):
        raise TypeError(F'type of `{n}` is `{type(n)}`')
    if n <= 2 or not isprime(n):
        raise ValueError(F'{n} <= 2 or {n} is not prime')

    phi: int = n - 1
    factors: dict[int, int] = factorint(phi)
    for g in range(2, n):
        if all(pow(g, phi // q, mod=n) != 1 for q in factors):
            yield g


def from_bijective(binary: bytes, /) -> int:
    result: int = 0
    for b in binary:
        result = (result << 8) + b + 1
    return result


def to_bijective(number: int, /) -> bytes:
    if number < 0:
        raise ValueError(F'{number} < 0')

    result: list[bytes] = []
    while number:
        number -= 1
        result.append(bytes([number & 0XFF]))
        number >>= 8
    return B''.join(reversed(result))


class Modulo(namedtuple('Modulo', ['bits', 'offset'])):
    @cached_property
    def mask(self) -> int:
        return (1 << self.bits) - 1

    @cached_property
    def modulo(self) -> int:
        return (1 << self.bits) - self.offset

    def __rmod__(self, number: int, /) -> int:
        if number < 0:
            number = self.modulo - (-number % self)

        while number.bit_length() > self.bits:
            number = (number & self.mask) + (number >> self.bits) * self.offset
        if number >= self.modulo:
            number -= self.modulo
        return number


class PolynomialHash(namedtuple('PolynomialHash', ['base', 'modulo', 'bits'])):
    @cached_property
    def mask(self) -> int:
        return (1 << self.bits) - 1

    def __call__(self, binary: bytes, /) -> int:
        result: int = 0
        for b in binary:
            result = (result * self.base + b + 1) % self.modulo
        return result & self.mask


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
            self.assertEqual(primitive_root(n), roots[0])
            self.assertEqual(list(primitive_roots(n)), roots)
            self.assertEqual(list(primitive_roots_sorted(n)), sorted(roots))


class TestBijective(TestCase):
    def test_bijective(self):
        for number, binary in [
            (0, B''), (1, B'\x00'), (2, B'\x01'), (256, B'\xFF'),
            (257,   B'\x00\x00'), (258,   B'\x00\x01'), (512,   B'\x00\xFF'),
            (513,   B'\x01\x00'), (514,   B'\x01\x01'), (768,   B'\x01\xFF'),
            (65537, B'\xFF\x00'), (65538, B'\xFF\x01'), (65792, B'\xFF\xFF'),
            (65793,    B'\x00\x00\x00'), (65794,    B'\x00\x00\x01'),
            (66048,    B'\x00\x00\xFF'), (66049,    B'\x00\x01\x00'),
            (66050,    B'\x00\x01\x01'), (66304,    B'\x00\x01\xFF'),
            (131073,   B'\x00\xFF\x00'), (131074,   B'\x00\xFF\x01'),
            (131328,   B'\x00\xFF\xFF'), (131329,   B'\x01\x00\x00'),
            (131330,   B'\x01\x00\x01'), (131584,   B'\x01\x00\xFF'),
            (131585,   B'\x01\x01\x00'), (131586,   B'\x01\x01\x01'),
            (131840,   B'\x01\x01\xFF'), (196609,   B'\x01\xFF\x00'),
            (196610,   B'\x01\xFF\x01'), (196864,   B'\x01\xFF\xFF'),
            (16777473, B'\xFF\x00\x00'), (16777474, B'\xFF\x00\x01'),
            (16777728, B'\xFF\x00\xFF'), (16777729, B'\xFF\x01\x00'),
            (16777730, B'\xFF\x01\x01'), (16777984, B'\xFF\x01\xFF'),
            (16842753, B'\xFF\xFF\x00'), (16842754, B'\xFF\xFF\x01'),
            (16843008, B'\xFF\xFF\xFF'),
            (16843009, B'\x00\x00\x00\x00')
        ]:
            self.assertEqual(from_bijective(binary), number)
            self.assertEqual(to_bijective(number), binary)


class TestModulo(TestCase):
    def test_rmod(self):
        modulo: Modulo = Modulo(bits=64, offset=1469)
        self.assertEqual((-modulo.modulo - 1) % modulo, modulo.modulo - 1)
        self.assertEqual(-modulo.modulo % modulo, 0)
        self.assertEqual((-modulo.modulo + 1) % modulo, 1)
        self.assertEqual(-1 % modulo, modulo.modulo - 1)
        self.assertEqual(0 % modulo, 0)
        self.assertEqual(1 % modulo, 1)
        self.assertEqual((modulo.modulo - 1) % modulo, modulo.modulo - 1)
        self.assertEqual(modulo.modulo % modulo, 0)
        self.assertEqual((modulo.modulo + 1) % modulo, 1)
        self.assertEqual(((1 << modulo.bits) - 1) % modulo, modulo.offset - 1)
        self.assertEqual((1 << modulo.bits) % modulo, modulo.offset)
        self.assertEqual(((1 << modulo.bits) + 1) % modulo, modulo.offset + 1)


class TestPolynomialHash(TestCase):
    @staticmethod
    def polynomial_hash(poly_hash: PolynomialHash, binary: bytes) -> int:
        base: int = poly_hash.base
        modulo: int = poly_hash.modulo.modulo

        result: int = 0
        for b in binary:
            result = (result * base + b + 1) % modulo
        return result & poly_hash.mask

    def test_call(self):
        modulo: Modulo = Modulo(bits=64, offset=1469)
        poly_hash: PolynomialHash = PolynomialHash(
            base=257,
            modulo=modulo,
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


if __name__ == "__main__":
    main()

    polynomial_hash: PolynomialHash = PolynomialHash(
        base=257,
        modulo=Modulo(bits=512, offset=38117),
        bits=64
    )
