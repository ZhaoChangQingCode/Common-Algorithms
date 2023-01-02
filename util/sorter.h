/**
 * @author 昭裳卿@QQ:956995844
 */

#define COMBSORT_DONOMINATOR 1.3F
#define size_t unsigned int

/**
 * 交换两个地址的值。
 */
template<typename T> inline void swap(T& a, T& b) noexcept {
    T tmp = a;
    a = b;
    b = tmp;
}

template<typename T> inline size_t length(T& a) {
    return sizeof(a) / sizeof(a[0]);
}

/**
 * 冒泡排序
 */
template<typename T> void bubbleSort(T& a, size_t low = 0, size_t high = length(a) - 1) {
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
 * 鸡尾酒排序；双向冒泡
 */
template<typename T> void cocktailShakerSort(T& a, size_t low = 0, size_t high = length(a) - 1) {
    while (low < high) {
        for (size_t i = high; i > low; i--) {
            if (a[i - 1] > a[i]) {
                swap(a[i - 1], a[i]);
            }
        }
        for (size_t i = low; i < high; i++) {
            if (a[i] > a[i + 1]) {
                swap(a[i], a[i + 1]);
            }
        }
    }
}

/**
 * 奇偶排序
 */
template<typename T> void oddEvenSort(T& a, size_t low = 0, size_t high = length(a) - 1) {
    bool sorted;
    do {
        for (size_t i = 1; i < high; i += 2) {
            if (sorted = (a[i] > a[i + 1])) {
                swap(a[i], a[i + 1]);
            }
        }
        for (size_t i = 0; i < high; i += 2) {
            if (sorted = (a[i] > a[i + 1])) {
                swap(a[i], a[i + 1]);
            }
        }
    } while (sorted);
}

/**
 * 地精排序，冒泡排序的优化版，减少了无效迭代。
 */
template<typename T> void gnomeSort(T& a, size_t low = 0, size_t high = length(a) - 1) {
    for (size_t i = low + 1, j; i < high; i++) {
        if (j > 0) {
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
template<typename T> void combSort(T& a, size_t low = 0, size_t high = length(a) - 1) {
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
template<typename T> void shellSort(T& a, size_t low = 0, size_t high = length(a) - 1) {
    size_t gap = (low + high) >> 1;
    while (gap > 0) {
        for (size_t i = gap, j; i < high; i++) {
            T& k = a[j = i];

            while (i >= gap && a[j - gap] > k) {
                a[j] = a[j - gap];
                j -= gap;
            }
            a[j] = k;
        }
        gap >>= 1;
    }
}

template<typename T> void johnySort(T& a, size_t low = 0, size_t high = length(0) - 1) {
    size_t gap = (low + high) >> 1;
    if (gap > 0) {
        for (size_t i = gap, j; i < high; i++) {
            T& k = a[j = i];

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
template<typename T> void doubleSelectionSort(T& a, size_t low = 0, size_t high = length(a) - 1) {
    size_t min_i, max_i;
    while (high - low > 1) {
        for (size_t i = low; i < high; i++) {
            T& k = a[i];

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
template<typename T> void insertionSort(T& a, size_t low = 0, size_t high = length(a) - 1) {
    for (size_t i = low + 1, j; i < high; i++) {
        T& k = a[j = i];

        if (k < a[j - 1]) {
            while (j-- >= 0 && k < a[j]) {
                a[j + 1] = a[j]; // {@code j} 已经自减
            }
            a[j + 1] = k;
        }
    }
}

/**
 * TODO: 计数排序
 */
template<typename T> void countingSort(T& a, size_t low = 0, size_t high = length(a) - 1) {
    T* tmp = new T[high - low] {0};

    for (size_t i = low; i < high; i++) {
        tmp[a[i]]++; // allocates key-value mapping, depositing values and its counts respectively
    }
    for (size_t i = low, j; i < high; i++) { // i -> a[i] 映射对于 值 -> 次数
        size_t count = a[j = i];

        for (size_t t = 0; t < count; t++) {
            a[i] = j;
        }
    }
    delete[] tmp; // removed from memory
}

/**
 * 快速排序以第一个元素为基准数 {@code pivot}. 右指针向左迭代至比基准数小的位置，
 * 左指针向右迭代至比基准数大的位置，然后交换左右，直至两指针相遇，交换基准数和
 * 相遇点。
 */
template<typename T> void quicksort(T& a, size_t low = 0, size_t high = length(a) - 1) {
    if (low < high) {
        size_t pivot_i = [](a, low, high) -> {
            size_t pivot_i = low;
            T& pivot = a[pivot_i];

            do {
                while (a[high--] >= pivot && low < high); // require {@code a[high]} < pivot
                while (a[low++] <= pivot && low < high);  // require {@code a[low]} > pivot

                swap(a[low], a[high]);
            } while (low < high);
            swap(a[pivot_i], a[low]);
            return low;
        }
        quicksort(a, low, pivot_i - 1);
        quicksort(a, pivot_i + 1, high);
    }
}

/**
 * 双轴快速排序
 */
template<typename T> void dualPivotQuicksort(T& a, size_t low = 0, size_t high = length(0) - 1) {
    if (low < high) {
        size_t left = low, right = high;
        T pivot1 = a[left], pivot2 = a[right];

        for (size_t i = low + 1; i < high; i++) {
            T& k = a[i];

            if (k < pivot1) {
                swap(a[i], a[++left]);
            } else if (k > pivot2) {
                swap(a[i], a[--right]);
            }
        }
        swap(a[low], a[left]);
        swap(a[high], a[right]);
        dualPivotQuicksort(a, low, left - 1);
        dualPivotQuicksort(a, left + 1, right - 1);
        dualPivotQuicksort(a, right + 1, high);
    }
}

/**
 * TODO: 归并排序
 */
template<typename T> void mergeSort(T& a, size_t low, size_t high) {}

/**
 * TODO: 二分法插入排序
 */
template<typename T> void binaryInsertionSort(T& a, size_t low, size_t high) {
    for (size_t i = low, j; i < high; i++) {
        T k = a[j = i];

        while (low < high) {
            size_t mid = (low + high) >> 1;

            if (a[mid] < k) {
                low = mid + 1;
            } else if (a[mid] > k) {
                high = mid - 1;
            }
        }
        while (j-- >= low) {
            swap(a[j], a[j + 1]);
        }
    }
}

/**
 * TODO: 二分法归并排序
 */
template<typename T> void binaryMergeSort(T& a, size_t low, size_t high) {}

/**
 * TODO: 堆排序
 */
template<typename T> void heapSort() {}

/**
 * TODO: 弱堆排序
 */
template<typename T> void weakHeapSort() {}

/**
 * TODO: 三元堆排序
 */
template<typename T> void ternaryHeapSort() {}

/**
 * TODO: 桶排序
 */
template<typename T> void bucketSort(T& a, size_t low, size_t high) {}

/**
 * TODO: 闪排序，桶排序的优化版。
 */
template<typename T> void flashSort() {}

inline size_t digits(int x) noexcept {
    size_t digits = 1;
    while (0 < x = (size_t)(x / pow(10, digit++)));
    return digits;
}

inline size_t digitAt(int x, int place) noexcept {
    return (int)(x / pow(10, place - 1)) % 10;
}


/**
 * TODO: 基数排序（LSD, Least Significant Digital）
 */
namespace lsd {
    template<typename T> void radixSort(T& a, size_t low, size_t high) {}
}

/**
 * TODO: 基数排序（MSD, Most Significant Digital）
 */
namespace msd {
    template<typename T> void radixSort(T& a, size_t low, size_t high) {}
}