#include <stdio.h>
#include <time.h>
#include <limits.h>

// 使用 __builtin_clzl 方法
unsigned int count_bits_clzl(unsigned long x) {
    return 8 * sizeof(long) - __builtin_clzl(x);
}

// 使用 BSR 方法，移到内联函数中
inline unsigned int count_bits_bsr(unsigned long x) {
    unsigned long index;
    __asm__("bsr %1, %0" : "=r" (index) : "r" (x));
    return index + 1;
}

int main() {
    unsigned long num = 0xFFFFFFFFFFFFFFF;  // 一个大的测试数
    struct timespec start, end;
    unsigned int bits;
    long long elapsed_ns;

    // 测试循环次数
    int iterations = 100000000;

    // 使用 __builtin_clzl 方法
    clock_gettime(CLOCK_MONOTONIC, &start);
    for (int i = 0; i < iterations; ++i) {
        bits = count_bits_clzl(num);
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    elapsed_ns = (end.tv_sec - start.tv_sec) * 1000000000LL + (end.tv_nsec - start.tv_nsec);
    printf("Using __builtin_clzl: %lld ns\n", elapsed_ns);

    // 使用 BSR 方法
    clock_gettime(CLOCK_MONOTONIC, &start);
    for (int i = 0; i < iterations; ++i) {
        bits = count_bits_bsr(num);
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    elapsed_ns = (end.tv_sec - start.tv_sec) * 1000000000LL + (end.tv_nsec - start.tv_nsec);
    printf("Using BSR: %lld ns\n", elapsed_ns);

    return 0;
}
