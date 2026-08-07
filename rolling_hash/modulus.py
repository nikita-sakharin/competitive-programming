from dataclasses import dataclass
from functools import cached_property
from unittest import TestCase, main


@dataclass(frozen=True, slots=False)
class Modulus:
    bits: int
    offset: int

    @cached_property
    def mask(self) -> int:
        return (1 << self.bits) - 1

    @cached_property
    def modulus(self) -> int:
        return (1 << self.bits) + self.offset

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


class TestModulus(TestCase):
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
