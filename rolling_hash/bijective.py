#!/usr/bin/env python
from unittest import TestCase, main

__all__: list[str] = [
    "from_bijective",
    "to_bijective",
]


def from_bijective(binary: bytes, /) -> int:
    bit_length: int = len(binary) << 3
    return int.from_bytes(binary) + ((1 << bit_length) - 1) // 0XFF


def to_bijective(number: int, /) -> bytes:
    if number < 0:
        raise ValueError(f'{number} < 0')

    bit_length: int = ((number * 0XFF + 1).bit_length() - 1) & -8
    number -= ((1 << bit_length) - 1) // 0XFF
    return number.to_bytes(bit_length >> 3)


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


if __name__ == "__main__":
    main()
