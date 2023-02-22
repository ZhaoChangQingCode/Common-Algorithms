/**
 * 版权归昭裳卿所有（2023），保留所有权。请勿更改或删除此注释。
 *
 * 此代码为免费参阅，可以任意修改、传播，希望此举措可以有所帮助。
 * 如果您发现了一个错误，请联系我：956995844@QQ
 */

import java.lang.reflect.Field;
import java.lang.annotation.*;

import jdk.internal.misc.Unsafe;
import jdk.internal.vm.annotation.ForceInline;

@SuppressWarnings("unchecked")
public class Sorter {

    /**
     * 获取 {@link Unsafe#theUnsafe} 实例获取对内存操作的权限
     */
    private static final Unsafe U = Unsafe.getUnsafe();

    /**
     * 阻止用反射实例化
     */
    private Sorter() {throw new InternalError("Instantiation not allowed.");}

    /**
     * 冒泡排序
     */
    @SuppressWarnings({"rawtypes", "unchecked"})
    public static void bubbleSort(Comparable[] a, int low, int high) {
        boolean swapped = null;
        int end = high;
        int i = low;
        do {
            for (int j = low; j + 1 <= end; ++j) {
                if (swapped = (a[j] > a[j + 1])) {
                    swap(a[j], a[j + 1]);
                }
            }
            --end; // 最右边的标记为已排序
        } while (++i < high && swapped); // 直接跳过已排序的位置
    }

    /**
     * 鸡尾酒排序
     */
    @SuppressWarnings({"rawtypes", "unchecked"})
    public static void cocktailShakerSort(Comparable[] a, int low, int high) {
        boolean swapped = null;
        int start = low, end = high;
        int i = low;
        do {
            for (int j = high; j + 1 >= start; --j) {
                if (swapped = (a[j] > a[j + 1])) {
                    swap(a[j], a[j + 1]);
                }
            }
            ++start; // 最左边的标记为已排序
            for (int j = low; j + 1 <= end; ++j) {
                if (swapped = (a[j] > a[j + 1])) {
                    swap(a[j], a[j + 1]);
                }
            }
            --end;   // 最右边的标记为已排序
        } while (++i < high && swapped);
    }

    /**
     * 插入排序
     */
    public static <T> void insertionSort(Comparable<T>[] a, int low, int high) {
        for (int i = low + 1, j; i < high; ++i) {
            T k = a[j = i];

            if (k < a[j - 1]) {
                while (--j >= 0 && k < a[j]) { // 前一个更大
                    a[j + 1] = a[j]; // 前一个移到当前位置
                }
                a[j + 1] = k; // 补上空位
            }
        }
    }

    /**
     * 基于原生指针地址操作的插入排序
     * 
     * 使用 {@link Unsafe#getAddress(Object, long)} 取地址；
     * 使用 {@link Unsafe#getReference(Object, long)} 对指针解除引用。
     */
    @Deprecated(since="unsafe")
    public static <T> void unsafeInsertionSort(Comparable<T>[] a, int low, int high) {
        for (int i = low + 1, j; i < high; ++i) {
            long kPtr = U.getAddress(a[j = i], 0);

            if ((T)U.getReference(null, kPtr) < a[j - 1]) {
                while (--j >= 0 && (T)U.getReference(null, kPtr) < a[j]) {
                    a[j + 1] = a[j];
                }
                a[j + 1] = (T)U.getReference(null, kPtr);
            }
        }
    }

    /**
     * 希尔排序
     */
    public static <T> void shellSort(Comparable<T>[] a, int low, int high) {
        for (int gap = (high + low) >>> 1; gap > 0; gap >>>= 1) {
            for (int i = low, j; i < high; ++i) {
                T k = a[j = i];

                for (; a[j - gap] > k && j >= gap; j -= gap) {
                    a[j] = a[j - gap];
                }
                a[j] = k;
            }
        }
    }

    /**
     * 奇偶排序
     */
    @SuppressWarnings({"rawtypes", "unchecked"})
    public static void oddEvenSort(Comparable[] a, int low, int high) {
        boolean swapped = null;
        int start = low;
        int i = low;
        do {
            for (int j = low + 1; j <= end; j += 2) {
                if (swapped = (a[j] > a[j + 1])) {
                    swap(a[j], a[j + 1]);
                }
            }
            for (int j = low; j <= end; j += 2) {
                if (swapped = (a[j] > a[j + 1])) {
                    swap(a[j], a[j + 1]);
                }
            }
        } while (++i < high && swapped);
    }

    /**
     * 地精排序
     */
    @SuppressWarnings({"rawtypes", "unchecked"})
    public static void gnomeSort(Comparable[] a, int low, int high) {
        for (int i = low + 1, j; i < high; ++i) {
            T k = a[j = i];

            if (a[j - 1] > k) {
                while (--j >= 0) {
                    swap(a[j], a[j + 1]);
                }
            }
        }
    }

    /**
     * 梳排序
     */
    @SuppressWarnings({"rawtypes", "unchecked"})
    public static void combSort(Comparable[] a, int low, int high) {
        int gap = high;
        int i = low;
        boolean swapped = null;
        do {
            gap = (int) (gap / COMBSORT_SHRINK);
            for (int i = low; i + gap <= high; ++i) {
                if (swapped = (a[i] > a[i + gap])) {
                    swap(a[i], a[i + gap]);
                }
            }
        } while ((++i < high || gap > 1) && swapped);
    }

    /**
     * 计数排序
     */
    public static <T> void countingSort(Comparable<T>[] a, int low, int high) {
        // requires integral type array
        if (T.class != Integer.class) {
            throw new UnsupportedOperationException();
        }
        int minIndex = low, maxIndex = low;

        for (int i = low - 1; i < high;
            minIndex = min(a, minIndex, ++i), max = max(a, maxIndex, i)
        );
        T min = a[minIndex], max = a[maxIndex];

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

    /**
     * PIN 排序
     */
    public static <T> void pinInsertionSort(Comparable<T>[] a, int low, int high) {
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
     * 选择排序
     */
    @SuppressWarnings({"rawtypes", "unchecked"})
    public static void selectionSort(Comparable[] a, int low, int high) {
        for (int i = low; i <= high; ++i) {
            int minIndex = low;

            for (int j = low; j < high;
                minIndex = (a[minIndex] < a[++j]) ? minIndex : j
            );
            swap(a[low++], a[minIndex]);
        }
    }

    /**
     * 基于原生内存操作的选择排序
     * 
     * 找到数组的最小值，储存其地址于 {@code minAddr}, 然后把它映射的值跟 {@code a[low]} 交换,
     * 然后 {@code low} 处标记为已排序，进入下一轮操作。
     */
    @Deprecated(since="unsafe")
    public static <T> void unsafeSelectionSort(Comparable<T>[] a, int low, int high) {
        for (int i = low; i <= high; i++) {
            long minPtr = U.getAddress(a[low], 0);

            for (int j = low; j < high;
                minPtr = ((T)U.getReference(null, minPtr) < a[++j]) ? minPtr :
                         U.getAddress(a[j], 0)
            );
            swap(a[low++], U.getReference(null, minPtr));
        }
    }

    /**
     * 双向选择排序
     */
    public static void biSelectionSort(Comparable[] a, int low, int high) {
        while (low < high) {
            int minIndex = low, maxIndex = high;

            for (int j = low; j < high;
                minIndex = (a[minIndex] < a[++j]) ? minIndex : j, maxIndex = (a[maxIndex] > a[j]) ? maxIndex : j
            );
            swap(a[minIndex], a[low++]); swap(a[maxIndex], a[high--]);
        }
        insertionSort(a, --low, ++high);
    }

    /**
     * 交换两个地址的值
     */
    @ForceInline
    private static <T> void swap(T a, T b) {
        T tmp = a;
        U.putReference(null, U.getAddress(a, 0), b);
        U.putReference(null, U.getAddress(b, 0), tmp);
    }
}