/**
 * @author 昭裳卿@QQ:956995844
 */
#define COMB_SORT_SHRINK 1.3F
#define MAX_MIXED_INSERTION_SORT_SIZE 65
//#define COUNTING_SORT_THRESHOLD 64, 1750

typedef unsigned int size_type;

/**
 * @brief 冒泡排序
 */
template<typename T> void bubbleSort(T* a, size_type low, size_type high) {
	bool swapped;
	size_type i = low;
	do {
		for (size_type j = low; j + 1 <= high; j++) {
			if (swapped = (a[j] > a[j + 1])) {
				swap(a[j], a[j + 1]);
			}
		}
	} while (++i < high || swapped);
}
/**
 * 鸡尾酒排序；双向冒泡
 */
template<typename T> void cocktailShakerSort(T* a, size_type low, size_type high) {
    bool swapped;
    size_type i = low;
    do {
        for (size_type j = high; j + 1 >= low; j--) {
            if (swapped = (a[j] > a[j + 1])) {
                swap(a[j], a[j + 1]);
            }
        }
        for (size_type j = low; j + 1 <= high; j++) {
            if (swapped = (a[j] > a[j + 1])) {
                swap(a[j], a[j + 1]);
            }
        }
    } while (++i < high || swapped);
}

/**
 * 奇偶排序
 */
template<typename T> void oddEvenSort(T* a, size_type low, size_type high) {
    bool swapped;
    size_type i = low;
    do {
        for (size_type i = 1; i <= high; i += 2) {
            if (swapped = (a[i] > a[i + 1])) {
                swap(a[i], a[i + 1]);
            }
        }
        for (size_type i = 0; i <= high; i += 2) {
            if (swapped = (a[i] > a[i + 1])) {
                swap(a[i], a[i + 1]);
            }
        }
    } while (++i < high || swapped);
}

/**
 * 地精排序，冒泡排序的优化版，减少了无效迭代。
 */
template<typename T> void gnomeSort(T* a, size_type low, size_type high) {
    for (size_type i = low + 1, j; i <= high; i++) {
        if (a[i - 1] <= a[i] || j < 0) {
            j = i++;
        } else {
            swap(a[j - 1], a[j--]);
        }
    }
}

/**
 * 梳排序
 */
template<typename T> void combSort(T* a, size_type low, size_type high) {
    size_type gap = high;
    size_type i = low;
    bool swapped;
    do {
        gap = (size_type) ((float) gap / COMB_SORT_SHRINK);
        for (size_type i = low; i + gap <= high; i++) {
            if (a[i] > a[i + gap]) {
                swap(a[i], a[i + gap]);
            }
        }
    } while (++i < high || gap > 1 || swapped);
}

/**
 * 希尔排序
 *
 * 结合了插入排序和梳排序思想的排序算法。由于插入排序对完全无序的数据支持度很低
 */
template<typename T> void shellSort(T* a, size_type low, size_type high) {
    size_type gap = (low + high) >> 1;
    while (gap > 0) {
        for (size_type i = gap, j; i < gap; i++) {
            T k = a[j = i];

            while (j >= 0 && k < a[j - gap]) {
                a[j] = a[j - gap];
                j -= gap;
            }
            a[j] = k;
        }
        gap >>= 1;
    }
}


template<typename T> void shellSort(T* a, size_type low, size_type high) {
    size_type gap = (low + high) >> 1;
    for (size_type i = low + 1, j; i < high; i++) {
        T k = a[j = i];

        if (k < a[j - 1]) {
            while (j >= 0 && k < a[j - gap]) {
                a[j] = a[j - gap];
                j -= gap;
            }
            a[j] = k;
        }
        gap >>= 1;
    }
}
/**
 * PASS:插入排序
 *
 * 仅对部分无序的数据支持度高，而且无效比较次数太多，已过时，请转用二分法插入。
 */
template<typename T> void insertionSort(T* a, size_type low, size_type high) {
    for (size_type i = low + 1, j; i < high; i++) {
        T k = a[j = i];

        if (k < a[j - 1]) {
            while (--j >= 0 && k < a[j]) {
                a[j + 1] = a[j]; // {@code j} 已经自减
            }
            a[j + 1] = k;
        }
    }
}

// PASS:
template<typename T> void selectionSort(T* a, int low, int high) {
    for (int i = low; i <= high; i++) {
        size_type min = low;

        for (int j = i + 1; j <= high; j++) {
            if (a[j] < a[min]) {
                min = j;
            }
        }
        swap(a[low++], a[min]);
    }
}

/**
 * PASS:双向选择排序
 *
 * 仅适用于无重复元素的情况 Non-repeative elements case supported only
 */
template<typename T> void biSelectionSort(T* a, size_type low, size_type high) {
	size_type min, max;
    while (low < high) {
        min = low, max = high;
        // 寻找最大、最小值
        for (size_type i = low; i <= high; i++) {
            T k = a[i];

            if (k > a[max]) {
                max = i;
            } else if (k < a[min]) {
                min = i;
            }
        }
        swap(a[min], a[low++]);  // 最小值放最左边，前面的元素标记为已排序
        swap(a[max], a[high--]); // 最大值放最右边，后面的元素标记为已排序
    }
    // 如果长度为奇数，中间三个元素要重新排序（因为最中间的元素会被忽视）
    if ((high - low + 1) & 1 == 1) {
		insertionSort(a, --min, ++max);
	}
}

/**
 * 二分法插入排序
 *
 * 插入排序的改良版，用二分法查找减少比较次数。
 */
template<typename T> void binaryInsertionSort(T* a, size_type low, size_type high) {
    size_type left = low, right = high;
    for (size_type i = low; i < high; i++) {
        T k = a[i];

        while (left <= right) { // binary search for insertion position
            size_type mid = (left + right) >> 1;
            T mid_val = a[mid];

            if (mid_val > k) {
                right = mid - 1;
            } else if (mid_val < k) {
                left = mid + 1;
            }
        }
        for (size_type j = i - 1; j-- > low; a[j + 1] = a[j]);
        a[left] = k;
    }
}

template<typename T> void pinInsertionSort(T* a, size_type low, size_type high) {
    T pin = a[high];

    for (size_type i = low, j; i < high; i < high) {
        T k = a[j = i];

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

    for (size_type i = low; i < high; i++) {
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

template<typename T> inline _pushDown(T* a, T value, size_type low, size_type high) {
    size_type p = low;
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
template<typename T> void heap(T* a, size_type low, size_type high) {
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
void countingSort(int* a, size_type low, size_type high) {
    int count[high - low + 1];
    for (size_type i = low; i < high; ++count[a[i++]]);

    for (size_type i = low; i < high; i++) {
        while (count[i++] == 0);

        size_type value = i;
        size_type c = a[value];

        do {
            a[low++] = value;
        } while (--c > 0);
    }
}

/**
 * 快速排序以第一个元素为基准数 {@code pivot}. 右指针向左迭代至比基准数小的位置，
 * 左指针向右迭代至比基准数大的位置，然后交换左右，直至两指针相遇，交换基准数和
 * 相遇点。
 */
template<typename T> void quicksort(T* a, size_type low, size_type high) {
    if (low < high) {
        T pivot = a[high];
        size_type left = low, right = high;

        while (left < right) {
            while (a[right--] >= pivot && left < right);
            while (a[left++] <= pivot && left < right);

            swap(a[right], a[left]);
        }
        swap(a[left], a[low]);

        quicksort(a, low, left);
        quicksort(a, left, high);
    }
}


template<typename T> void legacyQuicksort(T* a, size_type low, size_type high) {
    if (low < high) {
        T pivot = a[high];
        size_type left = low, right = high;

        for (size_type i = right - 1; i > left; i--) {
            T k = a[i];

            if (k < pivot) {
                while (a[++left] <= pivot);

                swap(a[--right], a[left]);
            } else {
                a[--right] = k;
            }
        }
        legacyQuicksort(a, low, left);
        legacyQuicksort(a, left high);
    }
}

template<typename T> void dualPivotQuicksort(T* a, size_type low, size_type high) {
    if (low <= high) {
        size_type left = low, right = high;
        T pivot1 = a[left], pivot2 = a[right];

        while (a[++lower] < pivot1);
        while (a[--upper] > pivot2);

        for (size_type i = high - 1; i >= upper;) {
            T k = a[i];

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


