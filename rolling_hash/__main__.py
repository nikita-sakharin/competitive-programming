#!/usr/bin/env python
from mpmath import (
    e, euler, fabs, floor, frac, ldexp, ln, log, phi, pi, power, sqrt,
    workprec,
)
from sympy import is_primitive_root

from bijective import to_bijective
from modulus import Modulus
from polynomial_hash import Finalizator, PolynomialHash

if __name__ == "__main__":
    modulus: Modulus = Modulus(bits=256, offset=-36113)
    finalize_modulus: Modulus = Modulus(bits=64, offset=-59)
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
            int(floor(ldexp(irrational, modulus.bits)))
            for irrational in irrationals
        ]
        multipliers = [
            base
            for base in multipliers
            if is_primitive_root(base, modulus.modulus)
        ]
        min_exp: int = modulus.bits + min(
            int(floor(log(irrational, 2)))
            for irrational in irrationals
        )
        powers: list = [
            power(modulus.modulus, exponent / modulus.bits)
            for exponent in range(min_exp, modulus.bits + 1)
        ]
        multipliers = sorted(
            multipliers,
            key=lambda b: min(powers, key=lambda p: fabs(b / p - 1))
        )
        multiplier: int = int(floor(ldexp(frac(phi), modulus.bits)))
        increment: int = int(floor(ldexp(frac(1 + sqrt(2)), modulus.bits)))
        seed: int = int(floor(ldexp(frac(1.5 + sqrt(13) / 2), modulus.bits)))
        finalize_multiplier: int = int(floor(ldexp(frac(e), finalize_modulus.bits)))
        finalize_increment: int = int(floor(ldexp(frac(pi), finalize_modulus.bits)))

    finalizator = Finalizator(
        multiplier=finalize_multiplier,
        increment=finalize_increment,
        modulus=finalize_modulus,
    )
    polynomial_hash: PolynomialHash = PolynomialHash(
        multiplier=multiplier,
        increment=increment,
        modulus=modulus,
        seed=seed,
        finalizator=finalizator,
    )
    for i in range(512):
        h: int = polynomial_hash(to_bijective(i))
        print(f"{h:064b}")
