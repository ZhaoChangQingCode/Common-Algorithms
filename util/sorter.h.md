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
## 目录
+ [冒泡排序](#)
+ [鸡尾酒排序（双向冒泡）](#)
+ [](#)
+ [](#)
+ [](#)
+ [](#)
+ [](#)
+ [](#)
+ [](#)
+ [](#)
+ [](#)
+ [](#)
+ [](#)
+ [](#)
+ [](#)
> ## 方法摘要
> 
>| 修饰符与类型 | 函数 | 描述 |
>|:----------:|:-----:|:------:|
>| template\<typename T\> void | [bubbleSort(T* a, size_t low, size_t high)](#bubble-sort) | 冒泡排序 |
>| template\<typename T\> void | [cocktailShakerSort(T* a, size_t low, size_t high)](#) | 双向冒泡 |
>| template\<typename T\> void | [oddEvenSort(T* a, size_t low, size_t high)]() | 奇偶排序 |
>| template\<typename T\> void | [gnomeSort(T* a, size_t low, size_t high)]() | 地精排序 |
>| template\<typename T\> void | [combSort(T* a, size_t low, size_t high)]() | 梳排序 |
>| template\<typename T\> void | [shellSort(T* a, size_t low, size_t high)]() | 希尔排序 |
>| template\<typename T\> void | [biSelectionSort(T* a, size_t low, size_t high)](#bi-selection-sort) | 双向选择 |
>| template\<typename T\> void | insertionSort(T* a, size_t low, size_t high) | 插入排序 |
>| template\<typename T\> void | pinInsertionSort(T* a, size_t low, size_t high) | pin插入 |
>| template\<typename T\> void | quicksort(T* a, size_t low, size_t high) | 快速排序 |
>| template\<typename T\> void | countingSort(T* a, size_t low, size_t high) | 计数排序 |
>| template\<typename T\> void | lsd::radixSort(T* a, size_t low, size_t high) | 基数排序（LSD） |
>| template\<typename T\> void | msd::radixSort(T* a, size_t low, size_t high) | 基数排序（MSD） |

> ## 函数详情
>> <h2 id="bubble-sort">冒泡排序</h2>
>> 最低级的排序算法。该算法为优化版。
>
>> <h2 id="bi-selection-sort">双向选择排序</h2>
>> 双向选择排序，选择排序的优化版。
>> 每轮遍历数组，将最小、最大值分别放在数组的左右两端，将左右端标记为已排序，然后开始下一轮
