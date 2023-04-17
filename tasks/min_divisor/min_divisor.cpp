#include "min_divisor.h"

int64_t MinDivisor(int64_t number) {
    if (number % 2 == 0) {
        return static_cast<int64_t>(2);
    }
    for (int64_t i = 3; i * i <= number; i += 2) {
        if (number % i == 0) {
            return static_cast<int64_t>(i);
        }
    }
    return static_cast<int64_t>(number);
}
