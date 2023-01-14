> ## 宏
>| 成员域 | 定义 |
>|:------:|:----|
>| size_type | unsigned int |

## 如何使用
每个函数的参数依次皆为 `T* a` 要排序的数组、`size_type low` 排序范围左端点、`size_type high` 排序范围右端点。
```C
size_t high = sizeof(a) / sizeof(a[0]); // 计算数组长度
bubbleSort(a, 0, --high);
```
你还可以用以下方法计算数组长度
```C
template<typename T, size_t S> size_t size(T (&a)[S]) {
    return S;
}
```
> ## 方法摘要
> 
>| 修饰符与类型 | 函数 | 描述 |
>|:----------:|:-----:|:------:|
>| template\<typename T\> void | [bubbleSort(T* a, size_type low, size_type high)](#bubble-sort) | 冒泡排序 |
>| template\<typename T\> void | [cocktailShakerSort(T* a, size_type low, size_type high)](#) | 双向冒泡 |
>| template\<typename T\> void | [oddEvenSort(T* a, size_type low, size_type high)]() | 奇偶排序 |
>| template\<typename T\> void | [gnomeSort(T* a, size_type low, size_type high)]() | 地精排序 |
>| template\<typename T\> void | [combSort(T* a, size_type low, size_type high)]() | 梳排序 |
>| template\<typename T\> void | [shellSort(T* a, size_type low, size_type high)]() | 希尔排序 |
>| template\<typename T\> void | [biSelectionSort(T* a, size_type low, size_type high)](#bi-selection-sort) | 双向选择 |
>| template\<typename T\> void | insertionSort(T* a, size_type low, size_type high) | 插入排序 |
>| template\<typename T\> void | pinInsertionSort(T* a, size_type low, size_type high) | pin插入 |
>| template\<typename T\> void | quicksort(T* a, size_type low, size_type high) | 快速排序 |
>| template\<typename T\> void | countingSort(T* a, size_type low, size_type high) | 计数排序 |
>| template\<typename T\> void | lsd::radixSort(T* a, size_type low, size_type high) | 基数排序（LSD） |
>| template\<typename T\> void | msd::radixSort(T* a, size_type low, size_type high) | 基数排序（MSD） |

> ## 冒泡排序（Bubble Sort） ##
> 时间复杂度最佳 O(n)，最差 O(n<sup>2</sup>)，平均 O(n<sup>2</sup>)；空间复杂度 O(1)
> 
> ## 鸡尾酒排序（Cocktail Shaker Sort） ##
> 冒泡排序的优化分支，
> 
> ## 奇偶排序（Odd-Even Sort） ##
> 冒泡排序的优化分支
> 
> ## 地精排序（Gnome Sort） ##
> 冒泡排序的优化分支
> 
> ## 梳排序（Comb Sort） ##
> 冒泡排序的优化分支
> 
> ## 希尔排序（Shell Sort） ##
> 时间复杂度最佳、最差 O(n·log<sup>2</sup>n)，平均 O(n·log<sub>2</sub>n)。
> 希尔排序是插入排序的优化分支，其由唐纳德·希尔（Donald Shell）于 1959 年所发表的论文《一种高效的排序算法》（A High-Apeed Sorting Procedure）中提出，由玛琳·梅茨纳·诺顿（Marlene Metzner Norton）首次实现。
> 
> ## 双向选择排序（Bidirection Selection Sort） ##
> 选择排序的优化版。每轮遍历寻找最小、最大值，然后分别放在数组的左右两端，然后将两端标记为已排序，然后开始下一轮。
> 
> ## 插入排序（Insertion Sort） ##
> 时间复杂度最佳 O(n)，最差 O(n<sup>2</sup>)，平均 O(n<sup>2</sup>)；空间复杂度 O(1)
>
> ## 计数排序（Counting Sort） ##
> 一种高效的排序算法，只支持排序整数和字符
> 
> ## 基数排序（Radix Sort） ##
> ## 快速排序（Quicksort） ##
> 一种高效的排序算法，
> ## 双轴快速排序（Dual-Pivot Quicksort） ##
> 快速排序的优化分支。
> ## 归并排序（Merge Sort） ##
> ## Tim Sort ##
> 一种高效的排序算法，归并排序的超级优化版本。由 Tim Peter 为 Python 发明。
