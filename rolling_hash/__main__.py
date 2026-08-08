from mpmath import (
    e, euler, fabs, floor, frac, ldexp, ln, log, nint, phi, pi, power, sqrt,
    workprec,
)
from sympy import is_primitive_root

from bijective import to_bijective
from modulus import Modulus
from polynomial_hash import PolynomialHash

if __name__ == "__main__":
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
        print(f"{h:064b}")
