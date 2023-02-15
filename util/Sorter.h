/**
 * 版权归昭裳卿所有（2023），保留所有权。请勿更改或删除此注释。
 * 
 * 此代码为免费参阅，可以任意修改、传播，希望此举措可以有所帮助。
 * 如果您发现了一个错误，请联系我：956995844@QQ
 */
#include <math.h>

typedef unsigned int size_type;

using COMBSORT_SHRINK     = 1.3F;
using COMBSORT_THRESHOLD  =   64;
using QUICKSORT_THRESHOLD =  512;

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
        T& k = a[j = i];

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
            T& k = a[j = i];

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
        gap = (size_type) (gap / COMBSORT_SHRINK);
        for (size_type i = low; i + gap <= high; i++) {
            if (swapped = (a[i] > a[i + gap])) {
                swap(a[i], a[i + gap]);
            }
        }
    } while (/* ++i < high || */gap > 1 || swapped);
}

/**
 * 计数排序（索引）
 */
template<class T> void countingSort(T* a, size_type low, size_type high) {
    T * min = &a[low], * max = &a[low];

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

/**
 * PIN 插入
 */
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

template<class T> T* min(T& a, T& b) {
    return (a > b) ? 
}

/**
 * 选择排序
 */
template<class T> void selectionSort(T* a, int low, int high) {
    for (int i = low; i <= high; i++) {
        T* min = &a[low]; // 实时更新指针

        for (size_type j = low; j < high;
            min = (*min < a[++j]) ? min : &a[j]
        );
        swap(a[low++], *min);
    }
}

/**
 * 双向选择排序
 */
template<class T> void biSelectionSort(T* a, size_type low, size_type high) {
    size_type size = high - low + 1;

    while (low < high) {
        T * min = &a[low], * max = &a[high];

        for (size_type j = low; j < high;
            min = (*min < a[++j]) ? min : &a[j],
            max = (*max > a[j])   ? max : &a[j]
        );
        swap(*min, a[low++]); swap(*max, a[high--]);
    }
    if (size & 1 == 1) insertionSort(a, --low, ++high);
}