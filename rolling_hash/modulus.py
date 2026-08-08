#!/usr/bin/env python
from dataclasses import dataclass
from functools import cached_property
from typing import final
from unittest import TestCase, main

__all__: list[str] = [
    "Modulus",
]


@final
@dataclass(frozen=True, kw_only=True)
class Modulus:
    bits: int
    offset: int

    @final
    @cached_property
    def mask(self) -> int:
        return (1 << self.bits) - 1

    @final
    @cached_property
    def modulus(self) -> int:
        return (1 << self.bits) + self.offset

    @final
    def __rmod__(self, number: int, /) -> int:
        if number < 0:
            number = self.modulus - (-number % self)

        while number.bit_length() > self.bits:
            number = (number & self.mask) - (number >> self.bits) * self.offset
        if number < 0:
            number += self.modulus
        if number >= self.modulus:
            number -= self.modulus
        return number


@final
class TestModulus(TestCase):
    @final
    def test_rmod(self):
        for modulus in [
            Modulus(bits=64, offset=-1469), Modulus(bits=64, offset=3103),
        ]:
            for point in [
                -(1 << modulus.bits), -modulus.modulus, 0,
                modulus.modulus, 1 << modulus.bits,
            ]:
                for delta in range(-4, 4):
                    number: int = point + delta
                    self.assertEqual(
                        number % modulus,
                        number % modulus.modulus,
                    )


if __name__ == "__main__":
    main()
