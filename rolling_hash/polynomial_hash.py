#!/usr/bin/env python
from dataclasses import dataclass
from functools import cached_property
from itertools import chain
from unittest import TestCase, main

from modulus import Modulus

__all__: list[str] = [
    "PolynomialHash",
]


@dataclass(frozen=True, slots=True)
class PolynomialHash:
    multiplier: int
    increment: int
    modulus: int
    seed: int
    bits: int

    @cached_property
    def mask(self) -> int:
        return (1 << self.bits) - 1

    def __call__(self, binary: bytes, /) -> int:
        state: int = self.seed
        for byte in chain(binary, (len(binary),)):
            state = (
                state * self.multiplier + byte + self.increment
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
        for byte in chain(binary, (len(binary),)):
            result = (result * multiplier + byte + increment) % modulus
        return result & poly_hash.mask

    def test_call(self):
        for modulus in [
            Modulus(bits=64, offset=-1469), Modulus(bits=64, offset=3103),
        ]:
            poly_hash: PolynomialHash = PolynomialHash(
                multiplier=257,
                increment=1,
                modulus=modulus,
                seed=1,
                bits=32,
            )
            for binary in [
                B"", B"\x00", B"\x01", B"\xFF",
                B"\x00\x00", B"\x00\x01", B"\x00\xFF",
                B"\x01\x00", B"\x01\x01", B"\x01\xFF",
                B"\xFF\x00", B"\xFF\x01", B"\xFF\xFF",
                B"\x00\x00\x00", B"\x00\x00\x01", B"\x00\x00\xFF",
                B"\x00\x01\x00", B"\x00\x01\x01", B"\x00\x01\xFF",
                B"\x00\xFF\x00", B"\x00\xFF\x01", B"\x00\xFF\xFF",
                B"\x01\x00\x00", B"\x01\x00\x01", B"\x01\x00\xFF",
                B"\x01\x01\x00", B"\x01\x01\x01", B"\x01\x01\xFF",
                B"\x01\xFF\x00", B"\x01\xFF\x01", B"\x01\xFF\xFF",
                B"\xFF\x00\x00", B"\xFF\x00\x01", B"\xFF\x00\xFF",
                B"\xFF\x01\x00", B"\xFF\x01\x01", B"\xFF\x01\xFF",
                B"\xFF\xFF\x00", B"\xFF\xFF\x01", B"\xFF\xFF\xFF",
                B"\x00\x00\x00\x00",
            ]:
                self.assertEqual(
                    poly_hash(binary),
                    self.polynomial_hash(poly_hash, binary)
                )


if __name__ == "__main__":
    main()
