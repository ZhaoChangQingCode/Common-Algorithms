/**
 * @author 昭裳卿@QQ:956995844
 */

#define COMBSORT_DONOMINATOR 1.3F
#ifndef size_t
#   define size_t unsigned int
#endif

/**
 * 交换两个地址的值
 */
template<typename T> inline void swap(T& a, T& b) noexcept {
    T tmp = a;
    a = b;
    b = tmp;
}

/**
 * 冒泡排序
 */
template<typename T> void bubbleSort(T* a, size_t low, size_t high) {
    bool swapped;
    do {
        for (size_t i = low + 1; i < high--; ++i) {
            if (swapped = (a[i - 1] > a[i])) {
                swap(a[i - 1], a[i]);
            }
        }
    } while (swapped);
}

/**
 * 地精排序
 */
template<typename T> void gnomeSort(T* a, size_t low, size_t high) {
    for (size_t i = low + 1, j; i < high; i++) {
        if (j != 0) {
            if (a[i - 1] <= a[i]) {
                j = ++i;
            } else {
                swap(a[j - 1], a[j--]);
            }
        } else {
            j = ++i;
        }
    }
}

/**
 * 梳排序
 */
template<typename T> void combSort(T* a, size_t low, size_t high) {
    size_t gap = high;
    bool swapped;

    do {
        gap = (size_t) (gap / COMBSORT_DONOMINATOR);

        for (size_t i = low; i + gap < high; i++) {
            if (swapped = (a[i] > a[i + gap])) {
                swap(a[i], a[i + gap]);
            }
        }
    } while (gap > 1 || swapped);
}

/**
 * 希尔排序
 */
template<typename T> void shellSort(T* a, size_t low, size_t high) {
    size_t gap = (low + high) >> 1;
    while (gap > 0) {
        for (size_t i = gap, j; i < high; i++) {
            T k = a[j = i];

            while (i >= gap && a[j - gap] > k) {
                a[j] = a[j - gap];
                j -= gap;
            }
            a[j] = k;
        }
        gap >>= 1;
    }
}

/**
 * 双向选择排序
 */
template<typename T> void dualSelectionSort(T* a, size_t low, size_t high) {
    size_t min_i, max_i;
    while (high - low > 1) {
        for (size_t i = low; i < high; i++) {
            T k = a[i];

            if (k > a[max_i]) {
                max_i = i;
            } else if (k < a[min_i]) {
                min_i = i;
            }
        }
        swap(a[min_i], a[low++]);
        swap(a[max_i], a[high--]);
    }
}

/**
 * 插入排序
 */
template<typename T> void insertionSort(T* a, size_t low, size_t high) {
    for (int i = low + 1, j; i < high; i++) {
        T k = a[j = i];

        if (k < a[j - 1]) {
            while (j-- >= 0 && k < a[j]) {
                a[j + 1] = a[j]; // {@code j} 已经自减
            }
            a[j + 1] = k;
        }
    }
}

/**
 * 快速排序
 */
template<typename T> void quicksort(T* a, size_t low, size_t high) {
    if (low < high) {
        size_t pivot_t = [](a, low, high) -> {
            size_t pivot_i = high;
            T pivot = a[left];

            while (low < high) {
                while (a[high--] >= pivot && low < high);
                while (a[low++] <= pivot && low < high);
                swap(a[low], a[high]);
            }
            swap(a[pivot_i], a[left]);
            return left;
        }
        quicksort(a, low, pivot_i - 1);
        quicksort(a, pivot_i + 1, high);
    }
}
