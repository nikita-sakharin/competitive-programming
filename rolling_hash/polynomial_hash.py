#!/usr/bin/env python
from collections.abc import Callable
from dataclasses import dataclass
from itertools import chain
from typing import ClassVar, Final, final
from unittest import TestCase, main

from modulus import Modulus

__all__: list[str] = [
    "Finalizator",
    "PolynomialHash",
]


@final
@dataclass(frozen=True, kw_only=True, slots=True)
class Finalizator:
    degree: ClassVar[Final[int]] = 3

    multiplier: int
    increment: int
    modulus: Modulus

    @final
    def __call__(self, state: int, /) -> int:
        return (
            pow(state, Finalizator.degree, mod=self.modulus.modulus)
            * self.multiplier + self.increment
        ) % self.modulus


@final
@dataclass(frozen=True, kw_only=True, slots=True)
class PolynomialHash:
    degree: ClassVar[Final[int]] = 3

    multiplier: int
    increment: int
    modulus: Modulus
    seed: int
    finalizator: Callable[[int], int]

    @final
    def __call__(self, binary: bytes, /) -> int:
        state: int = self.seed
        for byte in chain(binary, (len(binary),)):
            state = (
                pow(state, PolynomialHash.degree, mod=self.modulus.modulus)
                * self.multiplier + byte + self.increment
            ) % self.modulus

        return self.finalizator(state)


@final
class TestPolynomialHash(TestCase):
    @final
    @staticmethod
    def polynomial_hash(poly_hash: PolynomialHash, binary: bytes) -> int:
        multiplier: int = poly_hash.multiplier
        increment: int = poly_hash.increment
        modulus: int = poly_hash.modulus.modulus

        result: int = poly_hash.seed
        for byte in chain(binary, (len(binary),)):
            result = (
                pow(result, poly_hash.degree, mod=modulus)
                * multiplier + byte + increment
            ) % modulus
        return poly_hash.finalizator(result)

    @final
    def test_call(self):
        for modulus in [
            Modulus(bits=64, offset=-1469), Modulus(bits=64, offset=3103),
        ]:
            finalizator: Finalizator = Finalizator(
                multiplier=5,
                increment=1,
                modulus=Modulus(bits=32, offset=-209),
            )
            poly_hash: PolynomialHash = PolynomialHash(
                multiplier=257,
                increment=1,
                modulus=modulus,
                seed=1,
                finalizator=finalizator,
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
