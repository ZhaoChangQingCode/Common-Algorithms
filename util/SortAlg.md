```C++
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

```