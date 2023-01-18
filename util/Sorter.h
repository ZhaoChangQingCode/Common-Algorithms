/**
 * @author 昭裳卿@QQ:956995844
 */
#ifndef __cpluslpus
    #error "C++ supported only!"
#endif
#include <exception>
#include <map>

typedef unsigned int size_type;
using COMB_SORT_SHRINK = 1.3F;

/**
 * @brief 冒泡排序
 */
template<class T> void bubbleSort(T* a, size_type low, size_type high) {
    bool swapped;
    size_type end = high;
    size_type i = low;
    do {
        for (size_type j = low; j + 1 <= end; j++) {
            if (swapped = (a[j] > a[j + 1])) {
                swap(a[j], a[j + 1]);
            }
        }
        --end; // 最右边的标记为已排序
    } while (++i < high || swapped); // 直接跳过已排序的位置
}

/**
 * 鸡尾酒排序；双向冒泡
 */
template<class T> void cocktailShakerSort(T* a, size_type low, size_type high) {
    bool swapped;
    size_type start = low, end = high;
    size_type i = low;
    do {
        for (size_type j = high; j + 1 >= start; j--) {
            if (swapped = (a[j] > a[j + 1])) {
                swap(a[j], a[j + 1]);
            }
        }
        ++start; // 最左边的标记为已排序
        for (size_type j = low; j + 1 <= end; j++) {
            if (swapped = (a[j] > a[j + 1])) {
                swap(a[j], a[j + 1]);
            }
        }
        --end;   // 最右边的标记为已排序
    } while (++i < high || swapped);
}

/**
 * 插入排序
 *
 * 仅对部分无序的数据支持度高，而且无效比较次数太多，已过时，请转用二分法插入。
 */
template<class T> void insertionSort(T* a, size_type low, size_type high) {
    for (size_type i = low + 1, j; i < high; i++) {
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
 * @brief 希尔排序
 *
 * 插入排序的优化版
 */
template<class T> void shellSort(T* a, size_type low, size_type high) {
    for (size_type gap = (high - low) >> 1; gap > 0; gap >>= 1) {
        for (size_type i = gap, j; i < high; i++) {
            T k = a[j = i];

            while (j >= gap && a[j - gap] > k) {
                a[j] = a[j - gap];
            }
            a[j] = k;
        }
    }
}

/**
 * 奇偶排序
 */
template<class T> void oddEvenSort(T* a, size_type low, size_type high) {
    bool swapped;
    size_type start = low, end = high;
    size_type i = low;
    do {
        for (size_type i = 1; i <= end; i += 2) {
            if (swapped = (a[i] > a[i + 1])) {
                swap(a[i], a[i + 1]);
            }
        }
        end--;
        for (size_type i = 0; i <= end; i += 2) {
            if (swapped = (a[i] > a[i + 1])) {
                swap(a[i], a[i + 1]);
            }
        }
    } while (++i < high || swapped);
}

/**
 * 地精排序，冒泡排序的优化版，减少了无效迭代。
 */
template<class T> void gnomeSort(T* a, size_type low, size_type high) {
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
template<class T> void combSort(T* a, size_type low, size_type high) {
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



// PASS:
template<class T> void selectionSort(T* a, int low, int high) {
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
template<class T> void biSelectionSort(T* a, size_type low, size_type high) {
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
template<class T> void binaryInsertionSort(T* a, size_type low, size_type high) {
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

template<class T> void pinInsertionSort(T* a, size_type low, size_type high) {
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
template<class T> void quicksort(T* a, size_type low, size_type high) {
    if (low <= high) {
        T pivot = a[low];
        size_type left = low, right = high;

        while (true) {
            while (a[left] <= pivot && ++left < high);
            while (a[right] >= pivot && --right > low);

            if (left >= right) {
                break;
            }
            swap(a[left], a[right]);
        }
        a[low] = a[right];
        a[right] = pivot;

        quicksort(a, low, right - 1);
        quicksort(a, right + 1, high);
    }
}



// 数据必须是正整数！！！
template<class T> void countingSort(T* a, size_type low, size_type high) {
    size_type count[high - low + 1];
    // 统计元素数量，数组索引->值映射对应值->数量映射
    for (size_type i = low; i < high; ++count[a[++i]]);

    for (size_type i = low; i < high; i++) {
        while (count[++i] == 0);

        size_type value = i;
        int c = count[value];

        do {
            a[++low] = value;
        } while (--c > 0);
    }
}

/**
 * 求极值
 */
template<class T> struct Extremum {
    T min, max;
    Extremum(T* a, size_type low, size_type high) {
        T mi = a[low], ma = a[high];
        for (size_type i = low; i <= high; i++) {
            if (a[i] < mi) {
                mi = k;
            } else if (a[i] > ma) {
                ma = k;
            }
        }
        min = mi, max = ma;
    }
};

// 数据必须是整数！！
template<class T> void mappedCountingSort(T* a, size_type low, size_type high) {
    map<T,size_type> count;
    Extremum<T> e(a, low, high);
    // 初始化映射
    for (size_type i = e::min; i <= e::max; count[i++] = 0);
    // 统计
    for (size_type i = low; i <= high; ++count[a[i++]]);
    // 释放流
    for (map<T,size_type>::iterator i = count.begin; i != count.end; i++) {
        while (*i->second == 0);

        T value = *i->first;
        size_type c = *i->second;

        do {
            a[++low] = value;
        } while (--c > 0);
    }
}

template<class T> void quicksort(T* a, size_type low, size_type high) {
    if (low < high) {
        size_type upper, lower;
        T pivot = a[high];

        for (size_type i = low; i <= high; i++) {
            T k = a[i];

            if (k != pivot) {
                a[i] = pivot;

                if (k < pivot) {
                    while (a[++lower] < pivot);

                    if (a[lower] > pivot) {
                        a[--upper] = a[lower];
                    }
                    a[lower] = k;
                } else {
                    a[--upper] = k;
                }
            }
        }
        a[low] = a[lower];
        a[lower] = pivot;
    }
}

template<class T> void dualPivotQuicksort()
