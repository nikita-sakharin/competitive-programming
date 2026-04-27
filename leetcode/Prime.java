import java.math.BigInteger;
import java.util.Locale;
import java.util.function.Function;
import static java.lang.Math.log;
import static java.math.BigInteger.ONE;
import static java.math.BigInteger.TWO;

// javac -encoding UTF-8 -deprecation -Werror -Xdiags:verbose -Xlint:all Prime.java
// java -enableassertions Prime
// p = 2^128 - 15449
// p = 2^256 - 36113
// p = 2^512 - 38117
// p = 2^1024 - 1093337
public final class Prime {
    private static final int CERTAINTY = 1 << 21;

    private static final BigInteger
        THREE = BigInteger.valueOf(3L),
        FIVE = BigInteger.valueOf(5L),
        SIX = BigInteger.valueOf(6L),
        SEVEN = BigInteger.valueOf(7L),
        ELEVEN = BigInteger.valueOf(11L);

    private static final double LN2 = log(2D);

    private static final double curvature(
        final long difference,
        final int exponent
    ) {
        return log(difference) / LN2 / exponent;
    }

    private static final boolean isSafePrime(final BigInteger number) {
        return number.isProbablePrime(CERTAINTY)
            && number.shiftRight(1).isProbablePrime(CERTAINTY);
    }

    private static final BigInteger nextSafePrime(BigInteger number) {
        do
            number = number.nextProbablePrime();
        while (!isSafePrime(number));
        assert isSafePrime(number);

        return number;
    }

    private static final long[] previousNextDifference(
        final BigInteger number,
        final Function<BigInteger, BigInteger[]> function
    ) {
        final var previousNext = function.apply(number);
        return new long[]{
            number.subtract(previousNext[0]).longValueExact(),
            previousNext[1].subtract(number).longValueExact()
        };
    }

    private static final BigInteger[] previousNextPrime(
        final BigInteger number
    ) {
        final BigInteger previousPrime = previousPrime(number),
            nextPrime = number.nextProbablePrime();
        assert nextPrime.isProbablePrime(CERTAINTY);

        return new BigInteger[]{previousPrime, nextPrime};
    }

    private static final BigInteger[] previousNextSafePrime(
        final BigInteger number
    ) {
        final BigInteger previousPrime = previousSafePrime(number),
            nextPrime = nextSafePrime(number);

        return new BigInteger[]{previousPrime, nextPrime};
    }

    private static final BigInteger previousPrime(BigInteger number) {
        if (number.compareTo(TWO) <= 0)
            throw new IllegalArgumentException("number must be greater than 2");

        if (number.equals(THREE))
            return TWO;

        number = number.subtract(number.testBit(0) ? TWO : ONE);

        while (!number.isProbablePrime(CERTAINTY))
            number = number.subtract(TWO);
        assert number.isProbablePrime(CERTAINTY);

        return number;
    }

    private static final BigInteger previousSafePrime(BigInteger number) {
        if (number.compareTo(FIVE) <= 0)
            throw new IllegalArgumentException("number must be greater than 5");

        if (number.compareTo(SEVEN) > 0 && number.compareTo(ELEVEN) <= 0)
            return SEVEN;

        number = number.subtract(number.mod(SIX).add(ONE));
        while (!isSafePrime(number))
            number = number.subtract(SIX);
        assert isSafePrime(number);

        return number;
    }

    public static void main(final String[] args) {
        Locale.setDefault(Locale.ROOT);

        for (var exponent : new int[] {128, 256, 512}) {
            final var powerOfTwo = TWO.pow(exponent);

            final var difference =
                previousNextDifference(powerOfTwo, Prime::previousNextPrime);
            System.out.printf("2^%s - %s is prime\n", exponent, difference[0]);
            System.out.printf("curvature: %s%%\n",
                curvature(difference[0], exponent) * 100
            );

            System.out.printf("2^%s + %s is prime\n", exponent, difference[1]);
            System.out.printf("curvature: %s%%\n",
                curvature(difference[1], exponent) * 100
            );

            final var differenceSafe =
                previousNextDifference(powerOfTwo, Prime::previousNextSafePrime);
            System.out.printf("2^%s - %s is safe prime\n",
                exponent,
                differenceSafe[0]
            );
            System.out.printf("curvature: %s%%\n",
                curvature(differenceSafe[0], exponent) * 100
            );

            System.out.printf("2^%s + %s is safe prime\n",
                exponent,
                differenceSafe[1]
            );
            System.out.printf("curvature: %s%%\n",
                curvature(differenceSafe[1], exponent) * 100
            );

            System.out.println();
        }
    }
}
