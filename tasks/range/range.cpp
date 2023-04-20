#include "range.h"

std::vector<int> Range(int from, int to, int step) {
    std::vector<int> vector;
    if (from == to || (from < to && (step <= 0)) || (from > to && step >= 0)) {
        return vector;
    }
    for (int i = from; from < to ? i < to : i > to; i += step) {
        vector.push_back(i);
    }
    return vector;
}
