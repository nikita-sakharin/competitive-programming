#!/usr/bin/env python
from collections.abc import Iterable
from math import gcd
from sympy import factorint, isprime


def primitive_root(n: int, /) -> int:
    if not isinstance(n, int):
        raise TypeError(F'type of `{n}` is `{type(n)}`')
    if n <= 2 or not isprime(n):
        raise ValueError(F'{n} <= 2 or {n} is not prime')

    phi: int = n - 1
    factors: dict = factorint(phi)
    for g in range(2, n):
        if all(pow(g, phi // q, n) != 1 for q in factors):
            return g
    raise AssertionError()


def primitive_roots_naive(n: int, /):
    if not isinstance(n, int):
        raise TypeError(F'type of `{n}` is `{type(n)}`')
    if n <= 2 or not isprime(n):
        raise ValueError(F'{n} <= 2 or {n} is not prime')

    phi: int = n - 1
    factors: dict = factorint(phi)
    for g in range(2, n):
        if all(pow(g, phi // q, n) != 1 for q in factors):
            yield g


def primitive_roots(n: int, /):
    g: int = primitive_root(n)
    phi: int = n - 1
    for k in range(1, phi):
        if gcd(k, phi) == 1:
            yield pow(g, k, n)


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
assert sorted(primitive_roots(31)) == [ 3, 11, 12, 13, 17, 21, 22, 24]

assert sorted(primitive_roots_naive(3)) == [2]
assert sorted(primitive_roots_naive(5)) == [2, 3]
assert sorted(primitive_roots_naive(7)) == [3, 5]
assert sorted(primitive_roots_naive(11)) == [2, 6, 7, 8]
assert sorted(primitive_roots_naive(13)) == [2, 6, 7, 11]
assert sorted(primitive_roots_naive(17)) == [3, 5, 6, 7, 10, 11, 12, 14]
assert sorted(primitive_roots_naive(19)) == [2, 3, 10, 13, 14, 15]
assert sorted(primitive_roots_naive(23)) == [5, 7, 10, 11, 14, 15, 17, 19, 20, 21]
assert sorted(primitive_roots_naive(29)) == [2, 3, 8, 10, 11, 14, 15, 18, 19, 21, 26, 27]
assert sorted(primitive_roots_naive(31)) == [ 3, 11, 12, 13, 17, 21, 22, 24]
'''
r: int = 19
g: int = primitive_root(r)
print({g**alpha % r for alpha in range(0, r)})
'''
r: int = (1 << 127) - 1
for root in primitive_roots_naive(r):
    print(root)
