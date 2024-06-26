import static java.lang.Math.min;

final class Solution {
    private static int set(
        final int[] array,
        final int idx,
        final int value
    ) {
        final var previous = array[idx];
        array[idx] = value;
        return previous;
    }

    private static void rotate(
        final int[] array,
        final int from,
        final int to,
        int distance
    ) {
        final var size = to - from;
        if (size == 0)
            return;
        distance = distance % size;
        if (distance == 0)
            return;
        if (distance < 0)
            distance += size;

        final var bound = from + size - distance;
        for (int cycleStart = from, nMoved = 0; nMoved < size; ++cycleStart) {
            var displaced = array[cycleStart];
            var i = cycleStart;
            do {
                if (i >= bound)
                    i -= size;
                i += distance;
                displaced = set(array, i, displaced);
                ++nMoved;
            } while (i != cycleStart);
        }
    }

    private static int lowerBound(final int[] array, final int key) {
        return lowerBound(array, 0, array.length, key);
    }

    private static int lowerBound(
        final int[] array,
        int fromIndex,
        int toIndex,
        final int key
    ) {
        --toIndex;
        while (fromIndex <= toIndex) {
            final var middle = fromIndex + toIndex >>> 1;
            if (array[middle] < key)
                fromIndex = middle + 1;
            else
                toIndex = middle - 1;
        }
        return fromIndex;
    }

    private static int upperBound(final int[] array, final int key) {
        return upperBound(array, 0, array.length, key);
    }

    public static <T> int upperBound(
        final int[] array,
        int fromIndex,
        int toIndex,
        final int key
    ) {
        --toIndex;
        while (fromIndex <= toIndex) {
            final var middle = fromIndex + toIndex >>> 1;
            if (array[middle] > key)
                toIndex = middle - 1;
            else
                fromIndex = middle + 1;
        }
        return fromIndex;
    }

    private static void merge(
        final int[] array,
        final int from,
        final int middle,
        final int to
    ) {
        final int leftLen = middle - from, rightLen = to - middle;
        if (leftLen == 0 || rightLen == 0)
            return;
        final int leftIdx, rightIdx, distance, newMiddle;
        if (leftLen < rightLen) {
            rightIdx = middle + (rightLen - 1 >> 1) + 1;
            leftIdx = upperBound(array, from, middle, array[rightIdx - 1]);
            distance = rightIdx - middle;
            newMiddle = leftIdx + distance - 1;
        } else {
            leftIdx = from + (leftLen - 1 >> 1);
            rightIdx = lowerBound(array, middle, to, array[leftIdx]);
            distance = rightIdx - middle;
            newMiddle = leftIdx + distance;
        }
        rotate(array, leftIdx, rightIdx, distance);
        merge(array, from, leftIdx, newMiddle);
        merge(array, newMiddle + 1, rightIdx, to);
    }

    public final int[] sortArray(final int[] nums) {
        final int length = nums.length, half = length >> 1;
        var width = 1;
        while (width < length) {
            final var newWidth = width <= half ? width << 1 : length;
            var i = 0;
            while (i < length) {
                final int bound = length - i, newI = i + min(newWidth, bound);
                merge(nums, i, i + min(width, bound), newI);
                i = newI;
            }
            width = newWidth;
        }
        return nums;
    }
}
