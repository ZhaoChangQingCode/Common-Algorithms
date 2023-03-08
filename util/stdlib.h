/**
 * 为 num 个数据分配 size 字节大小的内存
 */
void* calloc(size_t num, size_t size);
int* ptr = new int[size];

/**
 * 释放 ptr 指向的内存
 */
void* free(void* ptr);
delete[] ptr;

/**
 * 分配 size 个字节的内存
 */
void* malloc(size_t size);

/**
 * 将 ptr 指向的内存空间改为 newSize 字节
 */
void* realloc(void ptr, size_t newSize);
ptr = new int[newSize];
