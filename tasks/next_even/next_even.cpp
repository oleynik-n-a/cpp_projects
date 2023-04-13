#include "next_even.h"

int64_t NextEven(int64_t n) {
    return static_cast<int64_t>(n % 2 == 0 ? n + 2 : n + 1);
}
