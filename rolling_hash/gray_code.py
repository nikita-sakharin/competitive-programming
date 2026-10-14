#!/usr/bin/env python
from unittest import TestCase, main

__all__: list[str] = [
    "from_gray_code",
    "to_gray_code",
]


def from_gray_code(binary: bytes, /) -> int:
    pass


def to_gray_code(number: int, /) -> bytes:
    if number < 0:
        raise ValueError(f"{number} < 0")
    
    length: int = max(1, number.bit_length())
    return (number ^ number >> 1).to_bytes(-(-length >> 3))


class TestBijective(TestCase):
    def test_gray_code(self):
        for number, binary in [
            (0, B"\x00"), (1, B"\x01"), (2, B"\x03"), (3, B"\x02"),
            (4, B"\x06"), (5, B"\x07"), (6, B"\x05"), (7, B"\x04"),
            (8, B"\x0C"), (9, B"\x0D"), (10, B"\x0F"), (11, B"\x0E"),
            (12, B"\x0A"), (13, B"\x0B"), (14, B"\x09"), (15, B"\x08"),
            (16, B"\x18"), (17, B"\x19"), (18, B"\x1B"), (19, B"\x1A"),
            (20, B"\x1E"), (21, B"\x1F"), (22, B"\x1D"), (23, B"\x1C"),
            (24, B"\x14"), (25, B"\x15"), (26, B"\x17"), (27, B"\x16"),
            (28, B"\x12"), (29, B"\x13"), (30, B"\x11"), (31, B"\x10"),
            (32, B"\x30"), (64, B"\x60"), (128, B"\xC0"), (256, B"\x01\x80"),
            (512, B"\x03\x00"), (1024, B"\x06\x00"), (2048, B"\x0C\x00"),
            (4096, B"\x18\x00"), (8192, B"\x30\x00"), (16384, B"\x60\x00"),
            (32768, B"\xC0\x00"),
        ]:
            # self.assertEqual(from_gray_code(binary), number)
            self.assertEqual(to_gray_code(number), binary)


if __name__ == "__main__":
    main()
