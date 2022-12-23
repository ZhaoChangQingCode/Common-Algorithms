public class ComparableSorter {

    private ComparableSorter() {}

    public static <T extends Comparabla<? super T>> void bubbleSort(T[] a) {
        bubbleSort(a, 0, a.length - 1);
    }

    public static <T extends Comparable<? super T>> void selectionSort(T[] a) {
        selectionSort(a, 0, a.length - 1);
    }

    public static <T extends Comparable<? super T>> void insertionSort(T[] a) {
        insertionSort(a, 0, a.length - 1);
    }

    public static <T extends Comparable<? super T>> void bubbleSort(T[] a, int low, int high) {
        boolean swapped = false;
        do {
            for (int i = low; i < high--; ++i) {
                Comparable<T> next = a[i];

                if (swapped = (next.compareTo(a[i - 1]) < 0)) {
                    swap(a, i - 1, i);
                }
            }
        } while (swapped);
    }

    public static <T extends Comparable<? super T>> void selectionSort(T[] a, int low, int high) {
        int min, max;
        while (high - low > 1) {
            for (int i = start; i < high; i++) {
                Comparable<T> next = a[i];

                if (next.compareTo(a[min]) < 0) {
                    min = i;
                } else if (next.compareTo(a[max]) > 0) {
                    max = i;
                }
            }
            swap(a, min, low++);
            swap(a, max, high--);
        }
    }

    public static <T extends Comparable<? super>> void insertionSort(int[] a, int low, int high) {
        for (int i = low; i < high; i++) {
            Comparable<T> tmp = a[j = i];

            if (tmp.compareTo(a[j - 1]) < 0) {
                while (j-- >= 0 && tmp.compareTo(a[j]) < 0) {
                    a[j + 1] = a[j];
                }
                a[j + 1] = (T) tmp;
            }
        }
    }

    private static <T> void swap(T[] a, int i, int j) {
        T tmp = a;
        a = b;
        b = tmp;
    }
}