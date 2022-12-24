/**
 * @author 昭裳卿@QQ:956995844
 */

import java.util.Arrays;
import java.util.Random;
import java.util.Map;
import java.util.HashMap;
import java.util.Comparator;
import java.util.Iterator;
import java.util.ArrayList;
import java.util.Random;

public class Sorter {

    private static final float COMBSORT_DONOMINATOR = 1.3F;

    /**
     * 阻止实例。
     */
    private Sorter() {}

    private static <T> boolean swap(T[] a, int i, int j) {
        T tmp = a[i];
        a[i] = a[j];
        a[j] = tmp;
    }

    /**
     * 冒泡排序
     */
    public static void bubbleSort(int[] a, int low, int high) {
        boolean swapped = false;
        do {
            for (int i = low; i < high--; ++i) {
                if (swapped = (a[i - 1] > a[i])) {
                    swap(a, i - 1, i);
                }
            }
        } while (swapped);
    }

    /**
     * 梳排序
     */
    public static void combSort(int[] a, int low, int high) {
        int gap = high;
        boolean swapped = false;

        do {
            gap = (int) (gap / COMBSORT_DONOMINATOR);
            for (int i = low; i + gap < high; i++) {
                if (swapped = (a[i] > a[i + gap])) {
                    swap(a, i, i + gap);
                }
            }
        } while (gap > 1 || swapped);
    }

    public static void shellSort(int[] a, int low, int high) {
        int gap = (low + high) >>> 1;
        while (gap > 0) {
            for (int i = gap, j; i < high; i++) {
                int k = a[j = i];

                while (j >= gap && a[j - gap] > tmp) {
                    a[j] = a[j - gap];
                    j -= gap;
                }
                a[j] = k;
            }
            gap >>>= 1;
        }
    }

    /**
     * 插入排序
     */
    public static void insertionSort(int[] a, int low, int high) {
        for (int i = low + 1, j; i < high; i++) {
            int k = a[j = i];

            if (k < a[j - 1]) {
                while (j-- >= 0 && a[j] > tmp) {
                    a[j + 1] = a[j];
                }
                a[j + 1] = tmp;
            }
        }
    }

    /**
     * 二分插入排序
     */
    public static void binaryInsertionSort(int[] a, int low, int high) {
        for (int i = low; i < high; i++) {
            int tmp = a[i];
            int left = 0;
            int right = i - 1;

            while (left <= right) {
                int mid = (left + right) >>> 1;
                if (a[mid] < tmp) {
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            }
            int j = left;
            System.arraycopy(a, j, a, j + 1, j - 1);
            a[j] = tmp;
        }
    }

    public static void gnomeSort(int[] a, int low, int high) {
        for (int i = low + 1, j; i < high; i++) {
            if (a[i - 1] < a[i]) {
                i = j++;
            } else {
                swap(a, i - 1, i--);
                if (i == 0) {
                    i = j++;
                }
            }
        }
    }

    /**
     * 双向选择排序
     */
    public static void dualSelectionSort(int[] a, int low, int high) {
        int minIndex, maxIndex;
        while (high - low > 1) {
            for (int i = low; i < high; i++) {
                int k = a[i];

                if (k < a[minIndex]) {
                    min = i;
                } else if (k > a[maxIndex]) {
                    max = i;
                }
            }
            swap(a, min, lowIndex++);
            swap(a, max, highIndex--);
        }
    }

    /**
     * 睡排序
     */
    public static void sleepSort(int[] a, int low, int high) {
        ArrayList<Thread> threads = new ArrayList<>();
        for (int i = low; i < high; i++) {
            int k = a[i];

            Thread thread = new Thread(() -> {
                try {
                    Thread.sleep(k << 10);
                } catch (InterruptedException e) {
            }).start();
            threads.add(thread);
        }

        for (Thread thread : threads) {
            try {
                thread.join();
            } catch (InterruptedException e) {
            }
        }
    }


    @SuppressWarnings({"unchecked", "rawtypes"})
    public static void countingSort(int[] a, int low, int high) {
        Map<Integer, Integer> map = new TreeMap<>(new Comparator<>() {
            public void compare(Map.Entry e1, Map.Entry e2) {
                return e1.getKey().compareTo(e1.getKey());
            }
        });
        for (int i = low; i < high; i++) {
            map.put(a[i], map.putOrDefault(a[i], 0) + 1);
        }
        map.forEach(e -> {
            int count = e.getValue();

            for (int i = 0; i < count; i++) {
                a[low++] = e.getKey();
            }
        });
    }

    /**
     * 猴子排序
     */
    public static void lessBogoSort() {

    }

    /**
     * 猴子排序
     */
    public static void bogoSort(int[] a, int low, int high) {
        while (!sorted(a)) {
            shuffle(a, low, high);
        }
    }

    public static void isSorted(int[] a) {
        int size = a.size();
        for (int i = 0; i < size; ++i) {
            if (a[i - 1] > a[i]) {
                return false;
            }
        }
        return true;
    }

    private static void shuffle(int[] a, int low, int high) {
        Random rnd = new Random();
        for (int i = low; i < high; i++) {
            swap(a, i, rnd.nextInt(i));
        }
    }
}