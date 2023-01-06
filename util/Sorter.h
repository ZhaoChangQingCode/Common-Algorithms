/**
 * @author 昭裳卿@QQ:956995844
 */
#define COMB_SORT_SHRINK 1.3F
// #define MAX_MIXED_INSERTION_SORT_SIZE 65
// #define COUNTING_SORT_THRESHOLD 64, 1750

typedef unsigned int size_t;

/**
 * 交换两个地址的值。
 */
template<typename T> inline void swap(T& a, T& b) noexcept {
    T tmp = a;
    a = b;
    b = tmp;
}

/**
 * @brief 冒泡排序
 */
template<typename T> void bubbleSort(T* (&a)[], size_t low, size_t high) {
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
template<typename T> void cocktailShakerSort(T* (&a)[], size_t low, size_t high) {
    bool swapped;
    do {
        for (size_t i = high; i > low; i--) {
            if (swapped = (a[i - 1] > a[i])) {
                swap(a[i - 1], a[i]);
            }
        }
        for (size_t i = low; i < high; i++) {
            if (swapped = (a[i] > a[i + 1])) {
                swap(a[i], a[i + 1]);
            }
        }
    } while (swapped);
}

/**
 * 奇偶排序
 */
template<typename T> void oddEvenSort(T* (&a)[], size_t low, size_t high) {
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
template<typename T> void gnomeSort(T* (&a)[], size_t low, size_t high) {
    for (size_t i = low + 1, j; i < high; i++) {
        if (a[i - 1] <= a[i] || j < 0) {
            j = ++i;
        } else {
            swap(a[j - 1], a[j--]);
        }
    }
}

/**
 * 梳排序
 */
template<typename T> void combSort(T* (&a)[], size_t low, size_t high) {
    size_t gap = high;
    bool swapped;
    do {
        gap = (size_t)((float)gap / COMB_SORT_SHRINK);
        for (size_t i = low; i + gap < high; i++) {
            if (swapped = (a[i] > a[i + gap])) {
                swap(a[i], a[i + gap]);
            }
        }
    } while (gap > 1 || swapped);
}

/**
 * 希尔排序
 *
 * 结合了插入排序和梳排序思想的排序算法。由于插入排序对完全无序的数据支持度很低
 */
template<typename T> void shellSort(T* (&a)[], size_t low, size_t high) {
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

/**
 * WARNING: 昭裳卿排序
 *
 * 
 */
template<typename T> void johnySort(T* (&a)[], size_t low, size_t high) {
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
    for (size_t i = low + 1; i < high; i++) {
        if (a[i - 1] <= a[i]) {
            while (++i < high && a[i - 1] <= a[i]);
        } else {
            while (++i < high && a[i - 1] >= a[i]); // 迭代至降序序列的最后一位

            for (size_t j = i, mid = (low + j) >> 1; mid < j;) { // 反转降序
                swap(a[low++], a[j--]);
            }
        }
    }
}

void selectionSort(T* (&a)[], size_t low, size_t high) {
    size_t min_i = low;
    for (size_t i = low, j; i < high; j = i++) {
        while (j++ < high) {
            T& k = a[j];

            if (k < a[min_i]) {
                min_i = j;
            }
        }
        swap(a[i], a[min_i]);
    }
}

/**
 * 双向选择排序
 */
template<typename T> void doubleSelectionSort(T* (&a)[], size_t low, size_t high) {
    size_t min_i, max_i;
    while (high - low > 1) {
        for (size_t i = low, j; i < high; i++) {
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
 *
 * 仅对部分无序的数据支持度高，而且无效比较次数太多，已过时，请转用二分法插入。
 */
template<typename T> void insertionSort(T* (&a)[], size_t low, size_t high) {
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
 * 二分法插入排序
 *
 * 插入排序的改良版，用二分法查找减少比较次数。
 */
template<typename T> void binaryInsertionSort(T* (&a)[], size_t low, size_t high) {
    size_t left = low, right = high;
    for (size_t i = low; i < high; i++) {
        T& k = a[i];

        while (left <= right) {
            size_t mid = (left + right) >> 1;
            T& mid_val = a[mid];

            if (mid_val > k) {
                high = mid - 1;
            } else if (mid_val < k) {
                low = mid + 1;
            }
        }
        for (size_t j = i - 1; j-- > low; a[j + 1] = a[j]);
        a[left] = k;
    }
}

template<typename T> void pinInsertionSort(T* (&a)[], size_t low, size_t high) {
    T& pin = a[high];

    for (size_t i = low, j; i < high; i < high) {
        T& k = a[j = i];

        if (k < a[i - 1]) {
            a[i] = a[--i];

            while (k < a[--i]) {
                a[i + 1] = a[i];
            }
            a[i + 1] = k;
        } else if (&& k > pin) {
            while (a[--] > pin);

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

    for (size_t i = low; i < high; i++) {
        T& a1 = a[i = low], a2 = a[++low];

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
                a[i + 2] = a[1];
            }
            a[++i + 1] = a2;

            while (a1 < a[--i]) {
                a[i + 1] = a[i];
            }
            a[i + 1] = a1;
        }
    }
}

template<typename T> inline _pushDown(* (&a)[], T value, size_t low, size_t high) {
    size_t p = low;
    for (int i; i < high; a[p] = a[p = i]) {
        i = (p << 1) - low + 2;

        if (k = high || a[i] < a[i - 1]) {
            --k;
        }
        if (a[i] <= value) {
            break;
        }
    }
    a[p] = value;
}

/**
 * 堆排序
 */
template<typename T> void heap(T* (&a)[], size_t low, size_t high) {
    for (int i = (low + high) >> 1; i > low;) {
        _pushDown(a, --i, a[i], low, high);
    }
    while (--high > low) {
        T& max = a[low];
        _pushDown(a, a[high], low, high);
        a[high] = max;
    }
}

/**
 * 计数排序
 */
void countingSort(size_T* (&a)[], size_t low, size_t high) {
    size_t* count = new size_t[high - low] {0};
    for (size_t i = low; i < high; ++count[a[i++]]);

    for (size_t i = low; i < high; i++) {
        while (count[i++] == 0);

        size_t& value = i;
        size_t& c = a[value];

        do {
            a[low++] = value;
        } while (--c > 0);
    }
    delete[] count;
}

/**
 * 快速排序以第一个元素为基准数 {@code pivot}. 右指针向左迭代至比基准数小的位置，
 * 左指针向右迭代至比基准数大的位置，然后交换左右，直至两指针相遇，交换基准数和
 * 相遇点。
 */
template<typename T> void quicksort(T* (&a)[], size_t low, size_t high) {
    if (low < high) {
        T& pivot = a[high];
        size_t left = low, right = high;

        do {
            while (a[--right] >= pivot);
            while (a[++left] <= pivot);

            swap(a[right], a[left]);
        } while (low < high);
        swap(a[left], a[low]);

        quicksort(a, low, left);
        quicksort(a, left, right);
    }
}


template<typename T> void legacyQuicksort(T* (&a)[], size_t low, size_t high) {
    if (low < high) {
        T& pivot = a[high];
        size_t left = low, right = high;

        for (size_t i = right - 1; i > left; i--) {
            T& k = a[i];

            if (k < pivot) {
                while (a[++left] <= pivot);

                if (a[left] > pivot) {
                    swap(a[--right], a[left]);
                }
            } else {
                a[--right] = k;
            }
        }
        quicksort(a, low, left);
        quicksort(a, left high);
    }
}

template<typename T> void dualPivotQuicksort(T* (&a)[], size_t low, size_t high) {
    if (low <= high) {
        size_t left = low, right = high;
        T &pivot1 = a[left], &pivot2 = a[right];

        while (a[++lower] < pivot1);
        while (a[--upper] > pivot2);

        for (size_t i = high - 1; i >= upper;) {
            T& k = a[i];

            if (k <= pivot1) { // 当前比左轴小
                while (left < k) { // 越界终止
                    if (a[++left] >= pivot1) {
                        if (a[left] > pivot2) { //
                            a[i] = a[--right];
                            a[right] = a[left];
                        } else {
                            a[i] = a[left];
                        }
                        a[left] = k;
                        break;
                    }
                }
            } else if (k >= pivot2) {
                swap(a[upper], a[i--]);
            }
        }
        a[low] = a[lower]; a[lower] = pivot1; // 左轴与 a[lower - 1] 交换
        a[end] = a[upper]; a[upper] = pivot2; // 右轴与 a[upper] 交换
        dualPivotQuicksort(a, low, left);
        dualPivotQuicksort(a, left, right);
        dualPivotQuicksort(a, right, high);
    }
}


