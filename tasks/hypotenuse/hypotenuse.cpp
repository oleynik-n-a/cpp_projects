#include "hypotenuse.h"

double CalculateHypotenuse(int64_t a, int64_t b) {
    return static_cast<double>((sqrt(static_cast<double>(a * a + b * b))));
}
