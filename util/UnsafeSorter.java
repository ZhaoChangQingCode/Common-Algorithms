/**
 * 版权归昭裳卿所有（2023），保留所有权。请勿更改或删除此注释。
 *
 * 此代码为免费参阅，可以任意修改、传播，希望此举措可以有所帮助。
 * 如果您发现了一个错误，请联系我：956995844@QQ
 */

import java.lang.reflect.Field;

import jdk.internal.vm.annotation.ForceInline;
import sun.misc.Unsafe;

public class UnsafeSorter {

    /**
     * 利用反射机制获取 Unsafe 实例直接操作内存
     */
    private static Unsafe unsafe;
    private static Field theUnsafe = Unsafe.class.getDeclaredField("theUnsafe");

    static {
        theUnsafe.setAcessible(true); // 关掉 JVM 编译器检查
        unsafe = theUnsafe.get(null);
    }

    /**
     * 阻止实例
     */
    private Sorter() {}

    @SuppressWarnings({"rawtypes", "unchecked"})
    public static void bubbleSort(Comparable[] a, int low, int high) {
        boolean swapped = false;
        int end = high;
        int i = low;
        do {
            for (int j = low; j + 1 <= end; j++) {
                if (swapped = (a[j] > a[j + 1])) {
                    swap(a[j], a[j + 1]);
                }
            }
            --end; // 最右边的标记为已排序
        } while (++i < high || swapped); // 直接跳过已排序的位置
    }

    @SuppressWarnings({"rawtypes", "unchecked"})
    public static void cocktailShakerSort(Comparable[] a, int low, int high) {
        boolean swapped = false;
        int start = low, end = high;
        int i = low;
        do {
            for (int j = high; j + 1 >= start; j--) {
                if (swapped = (a[j] > a[j + 1])) {
                    swap(a[j], a[j + 1]);
                }
            }
            ++start; // 最左边的标记为已排序
            for (int j = low; j + 1 <= end; j++) {
                if (swapped = (a[j] > a[j + 1])) {
                    swap(a[j], a[j + 1]);
                }
            }
            --end;   // 最右边的标记为已排序
        } while (++i < high || swapped);
    }

    public static void insertionSort(Comparable<T>[] a, int low, int high) {
        for (int i = low + 1, j; i < high; i++) {
            T k = a[j = i];

            if (k < a[j - 1]) {
                while (--j >= 0 && k < a[j]) { // 前一个更大
                    a[j + 1] = a[j]; // 前一个移到当前位置
                }
                a[j + 1] = k; // 补上空位
            }
        }
    }

    public static void shellSort(Comparable<T>[] a, int low, int high) {
        for (int gap = (high - low) >>> 1; gap > 0; gap >>>= 1) {
            for (int i = gap, j; i < high; i++) {
                T k = a[j = i];

                while (j >= gap && a[j - gap] > k) {
                    a[j] = a[j - gap];
                }
                a[j] = k;
            }
        }
    }

    @SuppressWarnings({"rawtypes", "unchecked"})
    public static void oddEvenSort(Comparable[] a, int low, int high) {
        boolean swapped = false;
        int start = low;
        int i = low;
        do {
            for (int j = 1; j <= end; j += 2) {
                if (swapped = (a[j] > a[j + 1])) {
                    swap(a[j], a[j + 1]);
                }
            }
            for (int j = 0; j <= end; j += 2) {
                if (swapped = (a[j] > a[j + 1])) {
                    swap(a[j], a[j + 1]);
                }
            }
        } while (++i < high || swapped);
    }

    @SuppressWarnings({"rawtypes", "unchecked"})
    public static void gnomeSort(Comparable[] a, int low, int high) {
        for (int i = low, j; i + 1 < high;) {
            if (i <= 0) {
                if ([i] <= a[i + 1]) { // 往后
                    j = i++;
                } else {
                    swap(a[i], a[i-- + 1]);
                }
            } else {
                i = j;
            }
        }
    }

    public static void combSort(Comparable[] a, int low, int high) {
        int gap = high;
        int i = low;
        boolean swapped = false;
        do {
            gap = (int) (gap / COMBSORT_SHRINK);
            for (int i = low; i + gap <= high; i++) {
                if (swapped = (a[i] > a[i + gap])) {
                    swap(a[i], a[i + gap]);
                }
            }
        } while (++i < high || gap > 1 || swapped);
    }

    public static <T> void countingSort(Comparable<T>[] a, int low, int high) {
        // requires integral type array
        if (T.class != Integer.class) {
            throw new UnsupportedOperationException();
        }
        T min = a[low], max = a[low];

        for (int i = low - 1; i < high;
            min = min(min, a[++i]), max = max(max, a[i])
        );

        if (min < 0 && max > 0) {
            min = -min;
            int negCount[min], count[max];

            for (int p = low - 1; p < high;
                a[++p] >= 0 ? ++count[a[p]] : ++negCount[-a[p]] // 负数转为正数
            );

            int i = low - 1;
            while (min > 0) {
                while (negCount[--min] == 0);

                T value = min;
                int c = negCount[value];

                do {
                    a[++i] = -value;
                } while (--c > 0);
            }

            while (i < high) {
                while (count[++i] == 0);

                T value = i;
                int c = count[value];

                do {
                    a[++i] = value;
                } while (--c > 0);
            }
        } else if (max < 0) {
            int count[max];

            for (int i = low - 1; i < high; ++count[-a[++i]]); // 负数转为正数

            for (int i = low - 1; max > 0;) {
                while (count[--max] == 0);

                T value = max;
                int c = count[value];

                do {
                    a[++i] = -value; // 将正数转为负数
                } while (--c > 0);
            }
        }
    }

    public static void pinInsertionSort(Comparable<T>[] a, int low, int high) {
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

    @ForceInline
    private static <T> void swap(T a, T b) {
        T tmp = a;
        unsafe.compareAndSwapObject(a, 0, a, b);
        unsafe.compareAndSwapObject(b, 0, b, tmp);
    }
}
