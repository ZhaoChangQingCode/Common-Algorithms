## 排序算法时间复杂度
| 算法 | 最佳 | 最差 | 平均 | 注 |
|:--:|:-|:-|:-|:-|
| 冒泡排序 | O(n)             | O(n<sup>2</sup>) | O(n<sup>2</sup>) |
| 选择排序 | O(n<sup>2</sup>) | O(n<sup>2</sup>) | O(n<sup>2</sup>) |
| 双向选择 | O(n)             | O(n<sup>2</sup>) | O(n<sup>2</sup>) |
| 希尔排序 | O(n log n)       | O(n<sup>2</sup>) | O(n log n)       |     
| 插入排序 | O(n)             | O(n<sup>2</sup>) | O(n<sup>2</sup>) |
| 梳排序   | O(n log n)       | O(n<sup>2</sup>) | O(n<sup>2</sup>) | 数组接近或已经有序时达到最佳 |
| 归并排序 | O(n log n)       | O(n log n)       | O(n log n) |
| 快速排序 | O(n log n)       | O(n<sup>2</sup>) | O(n log n) | 轴心为数组中位数时达到最佳 |
| 双轴快排 | O(n log n)       | O(n<sup>2</sub>)       | O(n log n) |
| Tim Sort | O(n)             | O(n log n)      | O(n log n) |
| 堆排序   | O(n log n)       | O(n log n)       | O(n log n) |
| 计数排序 |  | | |
| 桶排序 ||||
| 基数排序||||

## 排序算法空间复杂度
| 算法 | 注 |
|:--:|:-|
| 冒泡排序 |
| 选择排序 |
| 双向选择 |
| 希尔排序 | O(n log<sup>2</sup>n) |
| 插入排序 |  
| 梳排序   |
| 归并排序 |
| 快速排序 |
| 双轴快排 | O(n log n) |
| Tim Sort|
| 堆排序   |
| 计数排序 |
| 桶排序   |
| 基数排序 |

## 数据类型
| 类型 |  定义  |
|:--------|:------|
| size_type| unsigned int |

## 参数
> `a` - 要排序的数组的数据类型

> `low` - 

> `high` -

## 函数
| 修饰符与类型 | 返回类型 | 函数 | 描述 |
|:----------|:-- |-----:|:------|
| `template<class T>` | `void` | `        bubbleSort(T* a, size_type low, size_type high)` | 冒泡排序 |
| `template<class T>` | `void` | `cocktailShakerSort(T* a, size_type low, size_type high)` | 双向冒泡 |
| `template<class T>` | `void` | `       oddEvenSort(T* a, size_type low, size_type high)` | 奇偶排序 |
| `template<class T>` | `void` | `         gnomeSort(T* a, size_type low, size_type high)` | 地精排序 |
| `template<class T>` | `void` | `          combSort(T* a, size_type low, size_type high)` | 梳排序 |
| `template<class T>` | `void` | `         shellSort(T* a, size_type low, size_type high)` | 希尔排序 |
| `template<class T>` | `void` | `   biSelectionSort(T* a, size_type low, size_type high)` | 双向选择 |
| `template<class T>` | `void` | `     insertionSort(T* a, size_type low, size_type high)` | 插入排序 |
| `template<class T>` | `void` | `  pinInsertionSort(T* a, size_type low, size_type high)` | pin插入 |
| `template<class T>` | `void` | `         quicksort(T* a, size_type low, size_type high)` | 快速排序 |
| `template<class T>` | `void` | `      countingSort(T* a, size_type low, size_type high)` | 计数排序 |
| `template<class T>` | `void` | `    lsd::radixSort(T* a, size_type low, size_type high)` | 基数排序（LSD） |
| `template<class T>` | `void` | `    msd::radixSort(T* a, size_type low, size_type high)` | 基数排序（MSD） |



O(n)

O(n<sup>2</sup>)

O(n log<sub>2</sub>n)

O(log<sub>2</sub>n)

O(n log<sup>2</sup>n)

2<sup>2</sup>
2<sub>2</sub>
```C
template<class T> void swap(T& a, T& b) noexcept {
    if (a != b) {
        T tmp = a;
        a = b;
        b = tmp;
    }
}
```
