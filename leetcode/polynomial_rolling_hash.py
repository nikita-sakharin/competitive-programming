#!/usr/bin/env python
from collections.abc import Iterable
from math import gcd
from sympy import factorint, isprime


def primitive_root(n: int, /) -> int:
    return next(primitive_roots_naive(n))


def primitive_roots_naive(n: int, /) -> Iterable[int]:
    if not isinstance(n, int):
        raise TypeError(F'type of `{n}` is `{type(n)}`')
    if n <= 2 or not isprime(n):
        raise ValueError(F'{n} <= 2 or {n} is not prime')

    phi: int = n - 1
    factors: dict[int, int] = factorint(phi)
    for g in range(2, n):
        if all(pow(g, phi // q, n) != 1 for q in factors):
            yield g


def primitive_roots(n: int, /) -> Iterable[int]:
    g: int = primitive_root(n)
    phi: int = n - 1
    for k in range(1, phi):
        if gcd(k, phi) == 1:
            yield pow(g, k, n)


def to_bijective(number: int) -> bytes:
    result: list[bytes] = []
    while number:
        number -= 1
        result.append(bytes([number & 0XFF]))
        number >>= 8
    return B''.join(reversed(result))


assert primitive_root(3) == 2
assert primitive_root(5) == 2
assert primitive_root(7) == 3
assert primitive_root(11) == 2
assert primitive_root(13) == 2
assert primitive_root(17) == 3
assert primitive_root(19) == 2
assert primitive_root(23) == 5
assert primitive_root(29) == 2
assert primitive_root(31) == 3

assert sorted(primitive_roots(3)) == [2]
assert sorted(primitive_roots(5)) == [2, 3]
assert sorted(primitive_roots(7)) == [3, 5]
assert sorted(primitive_roots(11)) == [2, 6, 7, 8]
assert sorted(primitive_roots(13)) == [2, 6, 7, 11]
assert sorted(primitive_roots(17)) == [3, 5, 6, 7, 10, 11, 12, 14]
assert sorted(primitive_roots(19)) == [2, 3, 10, 13, 14, 15]
assert sorted(primitive_roots(23)) == [5, 7, 10, 11, 14, 15, 17, 19, 20, 21]
assert sorted(primitive_roots(29)) == [2, 3, 8, 10, 11, 14, 15, 18, 19, 21, 26, 27]
assert sorted(primitive_roots(31)) == [3, 11, 12, 13, 17, 21, 22, 24]

assert list(primitive_roots_naive(3)) == [2]
assert list(primitive_roots_naive(5)) == [2, 3]
assert list(primitive_roots_naive(7)) == [3, 5]
assert list(primitive_roots_naive(11)) == [2, 6, 7, 8]
assert list(primitive_roots_naive(13)) == [2, 6, 7, 11]
assert list(primitive_roots_naive(17)) == [3, 5, 6, 7, 10, 11, 12, 14]
assert list(primitive_roots_naive(19)) == [2, 3, 10, 13, 14, 15]
assert list(primitive_roots_naive(23)) == [5, 7, 10, 11, 14, 15, 17, 19, 20, 21]
assert list(primitive_roots_naive(29)) == [2, 3, 8, 10, 11, 14, 15, 18, 19, 21, 26, 27]
assert list(primitive_roots_naive(31)) == [3, 11, 12, 13, 17, 21, 22, 24]

assert to_bijective(0) == B''
assert to_bijective(1) == B'\x00'
assert to_bijective(2) == B'\x01'
assert to_bijective(256) == B'\xFF'
assert to_bijective(257) == B'\x00\x00'
assert to_bijective(258) == B'\x00\x01'
assert to_bijective(512) == B'\x00\xFF'
assert to_bijective(513) == B'\x01\x00'
assert to_bijective(65793) == B'\x00\x00\x00'

BASE: int = 257
MASK: int = 0XFFFFFFFFFFFFFFFF
MODULO: int = (1 << 512) - 38117


def _polynomial_hash(binary: bytes, base: int, modulo: int, mask: int) -> int:
    result: int = 0
    for b in binary:
        result = (result * base + b + 1) % modulo
    return result & mask


def prime512_38117_base257_64b(binary: bytes) -> int:
    return _polynomial_hash(binary, BASE, MODULO, MASK)
