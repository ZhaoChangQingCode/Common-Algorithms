
## 比较排序
|   算法   |   最佳   |   平均  |     最差     | 内存占用 | 是否稳定 |   方式   | 其他注意事项 |
|:--------:|:-------:|:-------:|:-----------:|:--------:|:-------:|:--------:|:--:|
| 快速排序  |n log n | n log n | n<sup>2</sup>|log n     | 否      | 分区     |
| 归并排序 | n log n | n log n | n log n      | n        | 是      | 合并     |
| 内省排序 | n log n | n log n | n log n      | log n    | 否      | 分区+选择 |
| 堆排序   | n log n | n log n | n log n      | 1        | 否      | 选择     |
| 插入排序  | n  | n<sup>2</sup>|n<sup>2</sup>| 1        | 是      | 插入     |
| 块排序   | n       | n log n | n log n      | 1        | 是      | 插入+合并|
| 提姆排序  | n       | n log n| n log n       | n       | 是      | 插入+合并|
| 选择排序|n<sup>2</sup>|n<sup>2</sup>|n<sup>2</sup>|1   | 否      | 选择     |
| 希尔排序|n log n|n<sup>$\frac 43$</sup>|n<sup>$\frac 32$</sup>|1|否|插入    |
| 耐心排序| n | - | n log n | n |否 | 插入+选择 |
| 平滑排序| n | n log n| n log n| 1 |否 |选择|
| 冒泡排序| n     |n<sup>2</sup>|n<sup>2</sup> | 1        | 是     | 交换    |
| 鸡尾酒排序|n |n<sup>2</sup>|n<sup>2</sup>|1 |是|交换
| 梳排序 | n log n |n<sup>2</sup>|n<sup>2</sup>|1 |否|交换|
| 地精排序|  n |n<sup>2</sup>|n<sup>2</sup>|1|是|交换|
| 奇偶排序| n | n<sup>2</sup>|n<sup>2</sup>|1|是|交换
| 费氏排序| - | n log n| n log n| 1|是 | ？|
| 树排序
| 循环排序
| 库排序

## 非比较排序
|   算法   | 最佳 | 平均 | 最差 | 内存占用 | 是否稳定 | 其他注意事项 |
|:--------:|:----:|:---:|:---:|:--------:|:-------:|:--:|
| 鸽巢排序 | - | n + 2<sup>k</sup>|n + 2<sup>k</sup>|2<sup>k</sup>| 是
| 桶排序   | - | n + k|n<sup>2</sup> · k| n · k|是
| 计数排序（整数键）|-| n + r|n + r|n + r|是|
| 基数排序（最低位优先法）|-|n · $\frac kd$|n · $\frac kd$|n + 2<sup>d</sup>|是
| 基数排序（最高位优先法）|-|n · $\frac kd$|n · $\frac kd$|n + 2<sup>d</sup>|是
| 闪排序 | n | n + r | n<sup>2</sup>| n |否

## 其它
|   算法   |   最佳   |   平均   |   最差   | 内存占用 | 是否稳定 | 是否比较 | 其他注意事项 |
|:--------:|:--------:|:--------:|:-------:|:--------:|:-------:|:-------:|:------------:|
| 珠排序    | n      | S        | S         |n<sup>2</sup>|不适用|否   
| 猴子排序  | n      |  n · n! |无界 n · n! |
| 投票排序|  n       | n        | n        |n<sup>2</sup>| 是

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
