#include "reduce_fraction.h"

int64_t ReduceFraction(int64_t numerator, int64_t denominator) {
    int64_t i = 2;
    int64_t* p = {&(numerator < denominator ? numerator : denominator)};
    bool is_simple = true;
    if (*p % 2 == 0) {
        is_simple = false;
    }
    for (int64_t j = 3; j * j <= *p; j += 2) {
        if (*p % j == 0) {
            is_simple = false;
        }
    }
    if (is_simple && numerator % denominator != 0 && denominator % numerator != 0) {
        return static_cast<int64_t>(numerator + denominator);
    }
    if (numerator == denominator) {
        return static_cast<int64_t>(2);
    }
    while (i <= *p) {
        if (numerator % i == 0 && denominator % i == 0) {
            numerator /= i;
            denominator /= i;
        } else {
            i += (i == 2 ? 1 : 2);
        }
    }
    return static_cast<int64_t>(numerator + denominator);
}
