#include <cstdint>
#include "factorization.h"

std::vector<std::pair<int64_t, int>> Factorize(int64_t x) {
    std::vector<std::pair<int64_t, int>> divisors;
    int64_t div = 2;
    int div_count = 0;

    bool is_simple = true;
    if (x % 2 == 0 && x != 2) {
        is_simple = false;
    }
    for (int64_t j = 3; j * j <= x; j += 2) {
        if (x % j == 0) {
            is_simple = false;
        }
    }
    if (is_simple) {
        divisors.emplace_back(x, 1);
        return divisors;
    }

    while (x > 1) {
        if (x % div == 0) {
            ++div_count;
            x /= div;
        }
        else {
            if (div_count != 0) {
                divisors.emplace_back(div, div_count);
                div_count = 0;
            }
            div += (div == 2 ? 1 : 2);
        }
    }
    if (div_count != 0) {
        divisors.emplace_back(div, div_count);
    }

    return divisors;
}
