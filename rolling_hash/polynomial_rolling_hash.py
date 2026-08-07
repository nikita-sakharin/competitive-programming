#!/usr/bin/env python
from collections import namedtuple
from functools import cached_property
from itertools import chain
from unittest import TestCase, main

from mpmath import (
    e, euler, fabs, floor, frac, ldexp, ln, log, nint, phi, pi, power, sqrt,
    workprec,
)
from sympy import is_primitive_root

from bijective import to_bijective
from modulus import Modulus

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
            state = (
                state * self.multiplier + b + self.increment
            ) % self.modulus

        result: int = 0
        while state:
            result ^= state & self.mask
            state >>= self.bits
        return result


class TestPolynomialHash(TestCase):
    @staticmethod
    def polynomial_hash(poly_hash: PolynomialHash, binary: bytes) -> int:
        multiplier: int = poly_hash.multiplier
        increment: int = poly_hash.increment
        modulus: int = poly_hash.modulus.modulus

        result: int = poly_hash.seed
        for b in binary:
            result = (result * multiplier + b + increment) % modulus
        result = (result * multiplier + increment) % modulus
        return result & poly_hash.mask

    def test_call(self):
        for modulus in [
            Modulus(bits=64, offset=-1469), Modulus(bits=64, offset=3103)
        ]:
            poly_hash: PolynomialHash = PolynomialHash(
                multiplier=257,
                increment=1,
                modulus=modulus,
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


if __name__ == "__main__":
    # main()

    modulus: Modulus = Modulus(bits=256, offset=-36113)
    with workprec(modulus.bits << 1):
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
            int(nint(ldexp(irrational, modulus.bits)))
            for irrational in irrationals
        ]
        multipliers = [
            base
            for base in multipliers
            if is_primitive_root(base, modulus.modulus) and base & 1
        ]
        # min_exp: int = modulus.bits + min(
        #     int(floor(log(irrational, 2)))
        #     for irrational in irrationals
        # )
        # powers: list = [
        #     power(modulus.modulus, exponent / modulus.bits)
        #     for exponent in range(min_exp, modulus.bits + 1)
        # ]
        # multipliers = sorted(
        #     multipliers,
        #     key=lambda b: min(powers, key=lambda p: fabs(b / p - 1))
        # )
        multiplier: int = multipliers[2]
        increment: int = int(nint(ldexp(frac(1 + sqrt(2)), modulus.bits)))
        seed: int = int(nint(ldexp(frac(1.5 + sqrt(13) / 2), modulus.bits)))

    polynomial_hash: PolynomialHash = PolynomialHash(
        multiplier=multiplier,
        increment=increment,
        modulus=modulus,
        seed=seed,
        bits=64,
    )
    for i in range(512):
        h: int = polynomial_hash(to_bijective(i))
        print(f'{h:064b}')
