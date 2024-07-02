#include <stdio.h>
#include <time.h>

unsigned int count_bits_div(unsigned long x) {
    unsigned int bits = 0;
    while (x > 0) {
        x /= 2;
        bits++;
    }
    return bits;
}

unsigned int count_bits_clzl(unsigned long x) {
    return 8 * sizeof(long) - __builtin_clzl(x);
}

int main() {
    unsigned long num = 0xFFFFFFFFFFFFFFF;  // 一个大的测试数
    clock_t start, end;
    unsigned int bits;

    // 使用除法方法
    start = clock();
    for (int i = 0; i < 1000000; ++i) {
        bits = count_bits_div(num);
    }
    end = clock();
    printf("Using division: %lu ticks\n", end - start);

    // 使用 __builtin_clzl 方法
    start = clock();
    for (int i = 0; i < 1000000; ++i) {
        bits = count_bits_clzl(num);
    }
    end = clock();
    printf("Using __builtin_clzl: %lu ticks\n", end - start);

    return 0;
}
