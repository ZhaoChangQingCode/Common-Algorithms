/**
 * @author 昭裳卿@QQ:956995844
 */
#ifndef __cpluslpus
    #error "C++ supported only!"
#endif
#include <exception>
#include <map>
#include <unordered_map>
#include <math.h>
#include <thread>
#include <vector>
#include <typeinfo>
#include <cassert>

typedef unsigned int size_type;

using COMB_SORT_SHRINK = 1.3F;
using COMB_SORT_THRESHOLD = 64;
using QUICKSORT_THRESHOLD = 512;

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
    size_type start = low;
    size_type i = low;
    do {
        for (size_type i = 1; i <= end; i += 2) {
            if (swapped = (a[i] > a[i + 1])) {
                swap(a[i], a[i + 1]);
            }
        }
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
    for (size_type i = low, j; i + 1 < high;) {
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

/**
 * 梳排序
 */
template<class T> void combSort(T* a, size_type low, size_type high) {
    size_type gap = high;
    size_type i = low;
    bool swapped;
    do {
        gap = (size_type) (gap / COMB_SORT_SHRINK);
        for (size_type i = low; i + gap <= high; i++) {
            if (swapped = (a[i] > a[i + gap])) {
                swap(a[i], a[i + gap]);
            }
        }
    } while (/* ++i < high || */gap > 1 || swapped);
}

/**
 * 计数排序（键值对映射的）
 */
template<class T> void mappedCountingSort(T* a, size_type low, size_type high) {
    std::ordered_map<T,size_type> count;
    T min = a[low], max = a[high];
    // 计算最大最小值
    // for (size_type i = low - 1; i < high;
    //     min = min(min, a[++i]), max = max(max, a[i])
    // );
    // 初始化映射容器
    for (size_type i = low - 1; i < high; count[++i] = 0);
    // 计数
    for (size_type i = low - 1; i < high; ++count[a[++i]]);

    for (std::map<T,size_type>::iterator i = count.begin; i != count.end; i++) {
        while (*++i->second == 0);

        T value = *i->first;
        size_type c = *i->second;

        do {
            a[++low] = value;
        } while (--c > 0);
    }
}

/**
 * 计数排序（索引）
 */
template<class T> void indexedCountingSort(T* a, size_type low, size_type high) {
    T min = a[low], max = a[low];

    for (size_type i = low - 1; i < high;
        min = min(min, a[++i]), max = max(max, a[i])
    );

    if (min < 0 && max > 0) {
        min = -min;
        size_type neg_count[min], count[max];

        for (size_type p = low - 1; p < high;
            a[++p] >= 0 ? ++count[a[p]] : ++neg_count[-a[p]] // 负数转为正数
        );

        size_type i = low - 1;
        while (min > 0) {
            while (neg_count[--min] == 0);

            T value = min;
            size_type c = neg_count[value];

            do {
                a[++i] = -value;
            } while (--c > 0);
        }

        while (i < high) {
            while (count[++i] == 0);

            T value = i;
            size_type c = count[value];

            do {
                a[++i] = value;
            } while (--c > 0);
        }
    } else if (max < 0) {
        size_type count[max];

        for (size_type i = low - 1; i < high; ++count[-a[++i]]); // 负数转为正数

        for (size_type i = low - 1; max > 0;) {
            while (count[--max] == 0);

            T value = max;
            size_type c = count[value];

            do {
                a[++i] = -value; // 将正数转为负数
            } while (--c > 0);
        }
    }
}

template<class T> void pinInsertionSort(T* a, size_type low, size_type high) {
    T pin = a[high];

    for (size_type i, p = high; ++low < high; ) {
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

    for (size_type i; low < high; ++low) {
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


template<class T> void countingSort(T* a, size_type low, size_type high) {
    if (sizeof(a[0]) <= 4 && typeid(T) != typeid(float)) { // 整数类型（char、short、int、long）？
        indexedCountingSort(a, low, high);
    } else {
        mappedCountingSort(a, low, high);
    }
}

/**
 * 选择排序
 */
template<class T> void selectionSort(T* a, int low, int high) {
    for (int i = low; i <= high; i++) {
        T min = a[low]; // 实时更新

        for (size_type j = low; j < high;
            min = min(min, a[++j])
        );
        swap(a[low++], min);
    }
}

/**
 * 双向选择排序
 */
template<class T> void biSelectionSort(T* a, size_type low, size_type high) {
    size_type size = high - low + 1;

    while (low < high) {
        T min = a[low], max = a[high];
        // 寻找最大、最小值
        for (size_type i = low; i < high; i++) {
            T k = a[i];

            if (k < min) {
                min = k;
            } else if (k > max) {
                max = k;
            }
        }
        swap(min, a[low++]);  // 最小值放最左边，前面的元素标记为已排序
        swap(max, a[high--]); // 最大值放最右边，后面的元素标记为已排序
    }

    if (size & 1 == 1) {
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

template<class T> void radixSort(T* a, size_type low, size_type high) {}

template<class T> void dualPivotQuicksort(T* a, size_type low, size_type high) {}

template<class T> void johnSort(T* a, size_type low, size_type high) {
    
}

template<class T> void sort(T* a, size_type low, size_type high) {
    size_type size = high - low + 1;

    /**
     * 对小容量数组使用希尔排序
     */
    if (size <= COMB_SORT_THRESHOLD) {
        shellSort(a, low, high);
        return;
    }

    /**
     * 对中等容量数组使用梳排序
     */
    if (size <= QUICKSORT_THRESHOLD) {
        combSort(a, low, high);
        return;
    }

    /**
     * 对大容量*整数*数组使用基数排序
     */
    if (size && sizeof(T) <= 4 && typeid(T) != typeid(float)) {
        radixSort(a, low, high);
        return;
    }

    /**
     * 使用双轴快速排序
     */
    dualPivotQuicksort(a, low, high);
}

template<class T> bool a(T* a, size_type low, size_type high) {
    for (size_type k = low + 1; k < high; ) {

        if (a[k - 1] < a[k]) {

            // 确认递增序列
            while (++k < high && a[k - 1] <= a[k]);

        } else if (a[k - 1] > a[k]) {

            // 确认递减序列
            while (++k < high && a[k - 1] >= a[k]);

            // 倒转
            for (size_type i = high - 1, j = k; ++i < --j && a[i] > a[j]) {
                swap(a[i], a[j]);
            }
        } else { // 确认连相等的序列
            for (T ak = a[k]; ++k < high && ak == a[k];);

            if (k < high) {
                continue;
            }
        }

        if (k == high) {
            return true;
        }

        if (k - low < MIN_RUN_SIZE) {
            return false;
        }
    }
}

template<class T> void pushDown() {
    size_type k;

    do {
        k = p << 1 - low + 2;

        if (k > high) {
            break; // 断行
        }
        if (k == high || a[k] < a[k - 1]) {
            --k;
        }
        a[p] = a[p = k];

    } while (a[k] > value);

    a[p] = value;
}