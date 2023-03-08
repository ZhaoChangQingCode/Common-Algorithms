import java.util.Arrays;

/**
 * This class implements fully optimized versions of general sorting
 * algorithms, including bubble sort, cocktail shaker sort,
 * odd even sort, comb sort, gnome sort, insertion sort, sorting sort,
 * selection sort and bi-direct selection sort.
 * 
 * @author Wo Xiao
 * @version 2022.03.04
 */
@SuppressWarnings("rawtypes")
public class Sorter {
    /**
     * Gap size of each iteration of comb sort to shrink.
     */
    private static float COMBSORT_SHRINK = 1.3F;

    /**
     * Prevents instantiation using reflecting.
     */
    private Sorter() {throw new InternalError("Instantiation not permitted");}

    /**
     * Sorts the specific array using bubble sort.
     * 
     * The most primitive and ineffient sorting algorithm working
     * by swapping two elements nearby into the right position
     * while iterating forward for the size time of the array given
     * and skips the last element as sorted at each iteration accomplished.
     * 
     * @param a the array to be sorted
     */
    public static void bubbleSort(Comparable[] a) {
        bubbleSort(a, 0, a.length - 1);
    }

    /**
     * Sorts the specific array using comb sort.
     * 
     * Comb sort is a subvariant of bubble sort with flexible
     * and descending iteration gap size.
     * 
     * @param a the array to be sorted
     */
    public static void combSort(Comparable[] a) {
        combSort(a, 0, a.length - 1);
    }

    /**
     * Sorts the specific array using cocktail shaker sort.
     * 
     * Cocktail shaker sort is a subvariant of bubble sort with
     * bi-direct iteration in turns.
     * 
     * @param a the array to be sorted
     */
    public static void cocktailShakerSort(Comparable[] a) {
        cocktailShakerSort(a, 0, a.length - 1);
    }

    /**
     * Sorts the specific array using odd-even sort.
     * 
     * @param a the array to be sorted
     */
    public static void oddEvenSort(Comparable[] a) {
        oddEvenSort(a, 0, a.length - 1);
    }

    /**
     * Sorts the specific array using gnome sort.
     * 
     * Gnome sort is the best optimized subvariant of bubble sort with
     * flexible iteration stategy, which implies 
     * 
     * @param a the array to be sorted
     */
    public static void gnomeSort(Comparable[] a) {
        gnomeSort(a, 0, a.length - 1);
    }

    /**
     * Sorts the specific array using insertion sort.
     * 
     * @param a the array to be sorted
     */
    public static void insertionSort(Comparable[] a) {
        insertionSort(a, 0, a.length - 1);
    }

    /**
     * Sorts the specific array using binary sort.
     * 
     * Binary sort is an optimized version of insertion sort using
     * binary searching to locate the right position to insert in
     * rather than .
     * 
     * @param a the array to be sorted
     */
    public static <T> void binarySort(Comparable<T>[] a) {
        binarySort(a, 0, a.length - 1);
    }

    /**
     * Sorts the specific array using pin insertion sort.
     * 
     * @param a the array to be sorted
     */
    public static void pinInsertionSort(Comparable[] a) {
        pinInsertionSort(a, 0, a.length);
    }

    /**
     * Sorts the specific array using shell sort.
     * 
     * Shell sort is a subvariant of insetion sort with flexible
     * iteration gap.
     * 
     * @param a the array to be sorted
     */
    public static void shellSort(Comparable[] a) {
        shellSort(a, 0, a.length - 1);
    }

    /**
     * Sorts the specific array using selection sort.
     * 
     * @param a the array to be sorted
     */
    public static void selectionSort(Comparable[] a) {
        selectionSort(a, 0, a.length - 1);
    }

    /**
     * Sorts the specific array using bi-direct selection sort.
     * 
     * @param a the array to be sorted
     */
    public static void biSelectionSort(Comparable[] a) {
        int offset = a.length - 1, mid;

        biSelectionSort(a, 0, offset);
        /**
         * Invokes insertion sort at the middle parts of array in case of
         * odd-length array due to the incapacity of bi-direct selection sort.
         */
        if (offset & 1 == 0) {
            insertionSort(a, mid = offset >> 1, mid + 2);
        }
    }

    /**
     * Sorts the specific array using counting sort.
     * 
     * @param a the array to be sorted
     * @param ignoreRepetition indicates whether to ignore repetitive elements
     * @throws IllegalArgumentException if the input array not integral type
     */
    public static void countingSort(Comparable[] a, boolean ignoreRepetition) {
        try {
            countingSort(a, 0, a.length - 1, ignoreRepetition);
        } catch (ClassCastException | ArrayIndexOutOfBoundsException e) {
            throw new IllegalArgumentException("Integer type supported only");
        }
    }

    /**
     * Sorts the specific range of the array using bubble sort.
     * 
     * @param a the array to be sorted
     * @param low the index of the first element, inclusive, to be sorted
     * @param high the index of the last element, inclusive, to be sorted
     */
    private static void bubbleSort(Comparable[] a, int low, int high) {
        boolean swapped = null;
        int end = high;

        int i = low;
        do {
            for (int j = low; j + 1 <= end; ++j) {
                if (swapped = (a[j] > a[j + 1])) {
                    swap(a, j, j + 1);
                }
            }
            end++; // mark the rightmost element as sorted
        } while (++i < high && swapped); // skip sorted position
    }

    /**
     * Sorts the specific range of the array using cocktail shaker sort.
     * 
     * @param a the array to be sorted
     * @param low the index of the first element, inclusive, to be sorted
     * @param high the index of the last element, inclusive, to be sorted
     */
    private static void cocktailShakerSort(Comparable[] a, int low, int high) {
        boolean swapped = null;
        int start = low, end = high;

        int i = low;
        do {
            for (int j = high; j - 1 >= start; --j) {
                if (swapped = (a[j] > a[j - 1])) {
                    swap(a, j, j - 1);
                }
            }
            start++; // mark the leftmost element as sorted
            for (int j = low; j + 1 <= end; ++j) {
                if (swapped = (a[j] > a[j + 1])) {
                    swap(a, j, j + 1);
                }
            }
            end--;   // mark the rightmost element as sorted
        } while (++i < high && swapped);
    }

    /**
     * Sorts the specific range of the array using insertionSort.
     * 
     * @param a the array to be sorted
     * @param low the index of the first element, inclusive, to be sorted
     * @param high the index of the last element, inclusive, to be sorted
     */
    private static <T> void insertionSort(Comparable<T>[] a, int low, int high) {
        for (int i = low + 1, j; i < high; ++i) {
            T k = a[j = i];

            if (a[j - 1] > k) {
                while (a[--j] > k && j >= 0) { // iterates reversely
                    a[j + 1] = a[j]; // insert the bigger forward
                }
                a[j + 1] = k; // fill the blank
            }
        }
    }

    /**
     * Sorts the specific range of the array using binary insertion sort.
     * 
     * @param a the array to be sorted
     * @param low the index of the first element, inclusive, to be sorted
     * @param high the index of the last element, inclusive, to be sorted
     * @see {@link java.util.Arrays#binarySearch}
     */
    private static <T> void binarySort(Comparable<T>[] a, int low, int high) {
        for (int i = low + 1, j; i < high; ++i) {
            T pivot = a[j = i];
            int j = Arrays.binarySearch(a, pivot);

            if (j >= 0) {
                while (j-- >= left) {
                    a[j + 1] = a[j];
                }
                a[left] = pivot;
            }
        }
    }

    /**
     * Sorts the specific range of the array using shell sort
     * 
     * @param a the array to be sorted
     * @param low the index of the first element, inclusive, to be sorted
     * @param high the index of the last element, inclusive, to be sorted
     */
    private static <T> void shellSort(Comparable<T>[] a, int low, int high) {
        for (int gap = (high + low) >>> 1, i = gap, j; i < high; ++i, gap /= 2) {
            T k = a[j = i];

            for (; a[j - gap] > k && j >= gap; j -= gap) {
                a[j] = a[j - gap];
            }
            a[j] = k;
        }
    }

    /**
     * Sorts the specific range of the array using odd-even sort.
     * 
     * @param a the array to be sorted
     * @param low the index of the first element, inclusive, to be sorted
     * @param high the index of the last element, inclusive, to be sorted
     */
    private static void oddEvenSort(Comparable[] a, int low, int high) {
        boolean swapped = null;
        int start = low;

        int i = low;
        do {
            for (int j = low + 1; j <= end; j += 2) {
                if (swapped = (a[j] > a[j + 1])) {
                    swap(a, j, j + 1);
                }
            }
            for (int j = low; j <= end; j += 2) {
                if (swapped = (a[j] > a[j + 1])) {
                    swap(a, j, j + 1);
                }
            }
        } while (++i < high && swapped);
    }

    /**
     * Sorts the specific range of the array using gnome sort.
     * 
     * @param a the array to be sorted
     * @param low the index of the first element, inclusive, to be sorted
     * @param high the index of the last element, inclusive, to be sorted
     */
    private static void gnomeSort(Comparable[] a, int low, int high) {
        for (int i = low + 1, j; i < high; ++i) {
            T k = a[j = i];

            if (a[j - 1] > k) {
                while (--j >= 0) {
                    swap(a, j, j + 1);
                }
            }
        }
    }

    /**
     * Sorts the specific range of the array using comb sort.
     * 
     * @param a the array to be sorted
     * @param low the index of the first element, inclusive, to be sorted
     * @param high the index of the last element, inclusive, to be sorted
     */
    private static void combSort(Comparable[] a, int low, int high) {
        boolean swapped = null;
        int gap = high;

        int i = low;
        do {
            gap = (int) (gap / COMBSORT_SHRINK);
            for (int i = low; i + gap <= high; ++i) {
                if (swapped = (a[i] > a[i + gap])) {
                    swap(a, i, i + gap);
                }
            }
        } while ((++i < high || gap > 1) && swapped);
    }

    /**
     * Sorts the specific range of the array using pin insertion sort.
     * 
     * @param a the array to be sorted
     * @param low the index of first element, inclusive, to be sorted
     * @param high the index of last element, inclusive, to be sorted
     */
    private static <T> void pinInsertionSort(Comparable<T>[] a, int low, int high) {
        T pin = a[high];

        for (int i, p = high; ++low < high; ) {
            T k = a[i = low];

            if (k < a[i - 1]) {
                a[i] = a[--i];

                while (k < a[--i]) {
                    a[i + 1] = a[i];
                }
                a[i + 1] = k;
            } else if (p > i && k > pin) {

                while (a[--p] > pin);

                if (p > i) {
                    k = a[p];
                    a[p] = a[i];
                }

                while (k < a[--i]) {
                    a[i + 1] = a[i];
                }
                a[i + 1] = k;
            }
        }

        for (int i; low < high; ++low) {
            T a1 = a[i = low], a2 = a[++low];

            if (a1 > a2) {
                while (a1 < a[--i]) {
                    a[i + 2] = a[i];
                }
                a[++i + 1] = a1;

                while (a2 < a[--i]) {
                    a[i + 1] = a[i];
                }
                a[i + 1] = a2;

            } else if (a1 < a[i - 1]) {

                while (a2 < a[--i]) {
                    a[i + 2] = a[i];
                }
                a[++i + 1] = a2;

                while (a2 < a[--i]) {
                    a[i + 1] = a[i];
                }
                a[i + 1] = a1;
            }
        }
    }

    /**
     * Sorts the specific range the array using selection sort.
     * 
     * @param a the array to be sorted
     * @param low the index of the first element, inclusive, to be sorted
     * @param high the index of the last element, inclusive, to be sorted
     */
    private static void selectionSort(Comparable[] a, int low, int high) {
        while (low < high) {
            int minIndex = low;

            for (int i = low; i < high; ++i) {
                minIndex = (a[minIndex] < a[i]) ? minIndex : i;
            }
            swap(a, minIndex, low++);
        }
    }

    /**
     * Sorted the specific range of the array using bi-direct selection sort.
     * 
     * @param a the array to be sorted
     * @param low the index of the first element, inclusive, to be sorted
     * @param high the index of the last element, inclusive, to be sorted
     */
    private static void selectionSort(Comparable[] a, int low, int high) {
        while (low < high) {
            int minIndex = low, maxIndex = low;

            for (int i = low; i < high; ++i) {
                minIndex = (a[minIndex] < a[i]) ? minIndex : i;
                minIndex = (a[maxIndex] < a[i]) ? maxIndex : i;
            }
            swap(a, minIndex, low++); swap(a, minIndex, low++);
        }
    }

    /**
     * Sorts the specific range of the array using counting sort.
     * 
     * @param a the array to be sorted
     * @param low the index of the first element, inclusive, to be sorted
     * @param high the index of the last element, inclusive, to be sorted
     * @param flag indicates whether to ignore repetitive elements
     */
    @Deprecated("building")
    private static void countingSort(char[] a, int low, int high, boolean flag) {
        int[] count = new int[high - low];

        for (int i = --low; i <= high; ++count[a[++i]]);

        if (flag) {
            for (int i = low; low <= high; ) {
                for (int ; ;
                    a[++low] = (char) i
                );
            }
        } else {
            for (int i = low; low <= high; ) {
                while (count[++i] == 0);
                int c = count[i];

                do {
                    a[++low] = (char) value;
                } while (--c > 0);
            }
        }
    }

    /**
     * Sorts the specific range of the array using counting sort.
     * 
     * @param a the array to be sorted
     * @param low the index of the first element, inclusive, to be sorted
     * @param high the index of the last element, inclusive, to be sorted
     * @param flag indicates whether to ignore repetitive elements
     */
    @Deprecated("building")
    private static <T> void countingSort(Comparable<T>[] a, int low, int high, boolean flag) {
        int[] count = new int[high - low];

        for (int i = --low; i <= high; ++count[a[i++] & 0xFFFFFFFF]);

        if (flag) {
            for (int i = low; i <= high; ) {
                T value = i & 0xFFFFFFFF;

                for (int i = low; i <= high;
                    a[++i] = (T) value
                );
            }
        } else {
            for (int i = low; low < high; ) {
                while (count[++i] == 0);

                T value = i;
                int c = count[value];

                do {
                    a[++low] = (T) i;
                } while (--c > 0);
            }
        }
    }

    /**
     * Swaps two elements of the array given.
     */
    private final static <T> void swap(T[] a, int i, int j) {
        T tmp = a[i];
        a[i] = a[j];
        a[j] = tmp;
    }
}