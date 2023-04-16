#include "sum_digits.h"


int64_t SumOfDigits(int64_t number) {
    int64_t ans = 0;
    while (number > 0) {
        const int div = 10;
        ans += number % div;
        number /= div;
    }
    return static_cast<int64_t>(ans);
}
