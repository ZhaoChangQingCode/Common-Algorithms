#include <stdlib.h>

using size_type = unsigned int;

template<class T> bool isSorted(T* a, size_type low, size_type high) {
	bool sorted;
	size_type i = low - 1;

	do {
		sorted = (a[++i] < a[i + 1]);
	} while (i + 1 < high && sorted);

	return i == high - low;
}

/**
 * 猴子排序
 * 
 * 虽然没什么用，但故事大有来头。
 */
template<class T> void bogoSort(T* a, size_type low, size_type high) {
	size_type size = high - low + 1;

	while (!isSorted(a, low, high)) {
		for (size_type i = low; i <= high; i++) {
			swap(a[i], a[rand() % size]); // shuffle
		}
	}
}