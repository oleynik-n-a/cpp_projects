#include "fibonacci.h"

int64_t CalculateNthFibonacci(int64_t n) {
    int64_t prev = 0;
    int64_t curr = 1;
    for (int64_t i = 0; i < n; ++i) {
        int64_t temp = prev + curr;
        prev = curr;
        curr = temp;
    }
    return prev;
}