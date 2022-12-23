


#include "原生排序算法.h"


/**
 * @author 昭裳卿@QQ:956995844
 */

#define COMBSORT_DONOMINATOR 1.3F

typedef unsigned int size_t;

/**
 * 交换两个地址的值
 */
template <typename T> inline void swap(T& a, T& b) {
    T tmp = a;
    a = b;
    b = tmp;
}

/**
 * 冒泡排序
 */
template <typename T> void bubbleSort(T a[], size_t low, size_t high) {
    bool swapped = false;
    do {
        for (int i = low + 1; i < high--; ++i) {
            if (swapped = (a[i - 1] > a[i])) {
                swap(a[i - 1], a[i]);
            }
        }
    } while (swapped);
}

/**
 * 梳排序
 */
template <typename T> void combSort(T a[], size_t low, size_t high) {
    int gap = high;
    bool swapped = false;
    do {
        gap = (int) (gap / COMBSORT_DONOMINATOR);
        for (int i = low; i + gap < high; i++) {
            if (swapped = (a[i] > a[i + gap])) {
                swap(a[i], a[i + gap]);
            }
        }
    } while (gap > 1 || swapped);
}

/**
 * 希尔排序
 */
template <typename T> void shellSort(T a[], size_t low, size_t high) {
    int gap = (low + high) >> 1;
    while (gap > 0) {
        for (int i = gap, j; i < high; i++) {
            int tmp = a[j = i];

            while (i >= gap && a[j - gap] > tmp) {
                a[j] = a[j - gap];
                j -= gap;
            }
            a[j] = tmp;
        }
        gap >>= 1;
    }
}

/**
 * 插入排序
 */
template <typename T> void insertionSort(T a[], size_t low, size_t high) {
    for (int i = low + 1, j; i < high; i++) {
        T tmp = a[j = i];

        if (tmp < a[j - 1]) {
            while (j-- >= 0 && tmp < a[j]) {
                a[j + 1] = a[j]; // {@code j} 已经自减
            }
            a[j + 1] = tmp;
        }
    }
}

/**
 * 双向选择排序
 */
template <typename T> void dualSelectionSort(T a[], size_t low, size_t high) {
    int min_i, max_i;
    while (high - low > 1) {
        for (int i = low; i < high; i++) {
            T candidate = a[i];

            if (candidate > a[max_i]) {
                max_i = i;
            } else if (candidate < a[min_i]) {
                min_i = i;
            }
        }
        swap(a[min_i], a[low++]);
        swap(a[max_i], a[high--]);
    }
}

第一个参数：要排序的数组
第二个参数：从哪个索引开始
第三个参数：从哪个索引结束

bubbleSort(,,)        冒泡排序
combSort(,,)          梳排序
shellSort(,,)         希尔排序
insertionSort(,,)     插入排序
selectionSort(,,)     选择排序
dualSelectionSort(,,) 双向选择排序

