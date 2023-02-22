/**
 * 版权归昭裳卿所有（2023），保留所有权。请勿更改或删除此注释。
 * 
 * 此代码为免费参阅，可以任意修改、传播，希望此举措可以有所帮助。
 * 如果您发现了一个错误，请联系我：956995844@QQ
 */
using COMBSORT_SHRINK     = 1.3F;
using COMBSORT_THRESHOLD  =   64;
using QUICKSORT_THRESHOLD =  512;

using namespace std;

/**
 * @brief 冒泡排序
 */
template<class T> void bubbleSort(T* a, size_t low, size_t high) {
    bool swapped = false;
    size_t end = high;
    size_t i = low;
    do {
        for (size_t j = low; j + 1 <= end; ++j) {
            if (swapped = (a[j] > a[j + 1])) {
                swap(a[j], a[j + 1]);
            }
        }
        --end; // 最右边的标记为已排序
    } while (++i < high && swapped); // 直接跳过已排序的位置
}

/**
 * 鸡尾酒排序；双向冒泡
 */
template<class T> void cocktailShakerSort(T* a, size_t low, size_t high) {
    bool swapped = false;
    size_t start = low, end = high;
    size_t i = low;
    do {
        for (size_t j = high; j - 1 >= start; --j) {
            if (swapped = (a[j - 1] < a[j])) {
                swap(a[j], a[j + 1]);
            }
        }
        ++start; // 最左边的标记为已排序
        for (size_t j = low; j + 1 <= end; ++j) {
            if (swapped = (a[j] > a[j + 1])) {
                swap(a[j], a[j + 1]);
            }
        }
        --end;   // 最右边的标记为已排序
    } while (++i < high && swapped);
}

/**
 * 奇偶排序
 * 
 * 两个迭代分别负责扫描奇、偶数次的元素
 */
template<class T> void oddEvenSort(T* a, size_t low, size_t high) {
    bool swapped = false;
    // size_t start = low;
    size_t i = low;
    do {
        for (size_t i = low + 1; i + 1 <= end; i += 2) {
            if (swapped = (a[i] > a[i + 1])) {
                swap(a[i], a[i + 1]);
            }
        }
        for (size_t i = low; i + 1 <= end; i += 2) {
            if (swapped = (a[i] > a[i + 1])) {
                swap(a[i], a[i + 1]);
            }
        }
    } while (++i < high && swapped);
}

/**
 * 地精排序，冒泡排序的优化版，减少了无效迭代。
 */
template<class T> void gnomeSort(T* a, size_t low, size_t high) {
    for (size_t i = low + 1, j; i < high; ++i) {
        T& k = a[j = i];

        if (a[j - 1] > k) {
            while (--j >= 0) { // 往左迭代
                swap(a[j], a[j + 1]); // 一路交换下去，直到见底
            }
        }
    } 
}

/**
 * 插入排序
 *
 * 仅对部分无序的数据支持度高，而且无效比较次数太多，已过时，请转用二分法插入。
 */
template<class T> void insertionSort(T* a, size_t low, size_t high) {
    for (size_t i = low + 1, j; i < high; ++i) {
        T& k = a[j = i];

        if (k < a[j - 1]) {
            while (a[--j] > k && j >= 0) { // 往左迭代
                a[j + 1] = a[j]; // 大的往右挪
            }
            a[j + 1] = k; // 小的补上空位
        }
    }
}


/**
 * @brief 希尔排序
 *
 * 插入排序的优化版
 */
template<class T> void shellSort(T* a, size_t low, size_t high) {
    for (size_t gap = (high + low) >> 1; gap > 0; gap >>= 1) {
        for (size_t i = gap, j; i < high; ++i) {
            T& k = a[j = i];

            for (; a[j - gap] > k && j >= gap; j -= gap) {
                a[j] = a[j - gap];
            }
            a[j] = k;
        }
    }
}

template<class T> void binarySort(T* a, size_t low, size_t high) {
    for (size_t i = low; i < high; ++i) {
        size_t left = low, right = high;
        T& k = a[j = i];

        while (left <= right) { // 查找该插入的 {@code left} 索引
            size_t mid = (left + right) >> 1;
            if (a[mid] < k) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        while (--j >= left) {
            a[j + 1] = a[j]; // 前一个移到当前位置
        }
        a[left] = k; // 补上空位
    }
}

/**
 * 梳排序
 */
template<class T> void combSort(T* a, size_t low, size_t high) {
    bool swapped;
    size_t gap = high;
    size_t i = low;
    do {
        gap = (size_t) (gap / COMBSORT_SHRINK);
        for (size_t i = low; i + gap <= high; ++i) {
            if (swapped = (a[i] > a[i + gap])) {
                swap(a[i], a[i + gap]);
            }
        }
    } while ((++i < high || gap > 1) && swapped);
}

/**
 * 计数排序（索引）
 */
template<class T> void countingSort(T* a, size_t low, size_t high) {
    T* pmin = &a[low], * pmax = &a[low];

    for (size_t i = low - 1; i < high;
        min = (*min < a[++i]) ? min : a[i], max = (*max > a[i]) ? max : a[i]
    );

    if (min < 0 && max > 0) {
        min = -min;
        size_t neg_count[min], count[max];

        for (size_t p = low - 1; p < high;
            a[++p] >= 0 ? ++count[a[p]] : ++neg_count[-a[p]] // 负数转为正数
        );

        size_t i = low - 1;
        while (min > 0) {
            while (neg_count[--min] == 0);

            T value = min;
            size_t c = neg_count[value];

            do {
                a[++i] = -value;
            } while (--c > 0);
        }

        while (i < high) {
            while (count[++i] == 0);

            T value = i;
            size_t c = count[value];

            do {
                a[++i] = value;
            } while (--c > 0);
        }
    } else if (max < 0) {
        size_t count[max];

        for (size_t i = low - 1; i < high; ++count[-a[++i]]); // 负数转为正数

        for (size_t i = low - 1; max > 0;) {
            while (count[--max] == 0);

            T value = max;
            size_t c = count[value];

            do {
                a[++i] = -value; // 将正数转为负数
            } while (--c > 0);
        }
    }
}

template<class T> void countingSort(T* a, size_t low, size_t high) {
    bool flag = false;
    int count[high - low];

    // 边计数边检查，如果有重复元素，使 {@code flag} 为 {@code true}
    for (size_t i = low - 1; i <= high; ++count[a[++i]] != 1 ? flag = true : 0);

    if (flag) {
        for (size_t i = low--; i <= high; i++) {
            while (count[++i] == 0);

            T& value = i;

            a[++low] = value;
        }
    } else {
        for (size_t i = low--; low < high;) {
            while (count[++i] == 0);

            T& value = i;
            size_t c = count;

            do {
                a[++low] = value;
            } while (--c > 0);
        }
    }
}

/**
 * PIN 插入
 */
template<class T> void pinInsertionSort(T* a, size_t low, size_t high) {
    T pin = a[high];

    for (size_t i, p = high; ++low < high; ) {
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

    for (size_t i; low < high; ++low) {
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
template<class T> void selectionSort(T* a, size_t low, size_t high) {
    for (size_t i = low; i <= high; ++i) {
        T* min = &a[low]; // 实时更新指针，其储存最小值指针

        for (size_t j = low; j < high;
            min = (*min < a[++j]) ? min : &a[j] // 获取
        );
        swap(a[low++], *min);
    }
}

/**
 * 双向选择排序
 */
template<class T> void biSelectionSort(T* a, size_t low, size_t high) {
    size_t size = high - low + 1;

    while (low < high) {
        T * min = &a[low], * max = &a[high];

        for (size_t j = low; j < high;
            min = (*min < a[++j]) ? min : &a[j],
            max = (*max > a[j])   ? max : &a[j]
        );
        swap(*min, a[low++]); swap(*max, a[high--]);
    }
    insertionSort(a, --low, ++high);
}

#include <cmath>

/**
 * 猴子排序
 */
template<class T> void bogoSort(T* a, size_t low, size_t high) {
    size_t size = high - low + 1;
    while ([=] {
        bool sorted = true;
        for (size_t i = low - 1; i + 1 < high && sorted;
            sorted = (a[++i] < a[i + 1])
        );
        return i == high - low;
    }) {
        for (size_t i = low; i <= high; ++i) {
            swap(a[i], a[rand() % size]);
        }
    }
}
