#!/usr/bin/env python
from collections.abc import Iterator
from math import gcd
from unittest import TestCase, main

from sympy import factorint, primitive_root, totient

__all__: list[str] = [
    "has_primitive_root",
    "primitive_roots",
    "primitive_roots_sorted",
]


def has_primitive_root(n: int, /) -> bool:
    if n < 2:
        raise ValueError(f"{n} < 2")

    factors: dict[int, int] = factorint(n)
    return (
        len(factors) == 1 and factors.get(2, 0) < 3
        or len(factors) == 2 and factors.get(2, 0) == 1
    )


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
    stop: int | None = None,
) -> Iterator[int]:
    if stop is None:
        stop = n

    if not all(map(lambda arg: isinstance(arg, int), (n, start, stop))):
        raise TypeError(", ".join(
            f"type of `{arg}` is `{type(arg)}`"
            for arg in (n, start, stop)
        ))
    if not 2 <= start <= stop <= n or not has_primitive_root(n):
        raise ValueError(
            f"Inequation `2 <= {start} <= {stop} <= {n}` is not satisfied"
            f" or `{n}` has no primitive roots"
        )

    phi: int = int(totient(n))
    factors: dict[int, int] = factorint(phi)
    for g in range(start, stop):
        if gcd(g, n) == 1 and all(pow(g, phi // p, mod=n) != 1 for p in factors):
            yield g


class TestPrimitiveRoot(TestCase):
    def test_primitive_roots(self):
        for n, roots in [
            (3, [2]), (4, [3]), (5, [2, 3]), (6, [5]), (7, [3, 5]),
            (9, [2, 5]), (10, [3, 7]), (11, [2, 8, 7, 6]), (13, [2, 6, 11, 7]),
            (14, [3, 5]), (17, [3, 10, 5, 11, 14, 7, 12, 6]), (18, [5, 11]),
            (19, [2, 13, 14, 15, 3, 10]), (22, [7, 13, 17, 19]),
            (23, [5, 10, 20, 17, 11, 21, 19, 15, 7, 14]),
            (25, [2, 8, 3, 12, 23, 17, 22, 13]), (26, [7, 11, 19, 15]),
            (27, [2, 5, 20, 23, 11, 14]),
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
            (61, [2, 6, 35, 18, 44, 54, 10, 30, 59, 55, 26, 43, 17, 7, 51,
                  31]),
        ]:
            self.assertEqual(list(primitive_roots(n)), roots)
            self.assertEqual(list(primitive_roots_sorted(n)), sorted(roots))

    def test_has_primitive_roots(self):
        has_root: set[int] = {
            2, 3, 4, 5, 6, 7, 9, 10, 11, 13, 14, 17, 18, 19, 22, 23, 25, 26,
            27, 29, 31, 34, 37, 38, 41, 43, 46, 47, 49, 50, 53, 54, 58, 59, 61,
            62, 67, 71, 73, 74, 79, 81, 82, 83, 86, 89, 94, 97, 98, 101, 103,
            106, 107, 109, 113, 118, 121, 122, 125, 127, 131, 134, 137, 139,
        }
        for n in range(-1, max(has_root) + 1):
            if n in range(-2, 2):
                self.assertRaises(ValueError, has_primitive_root, n)
            else:
                self.assertEqual(has_primitive_root(n), n in has_root)


if __name__ == "__main__":
    main()
