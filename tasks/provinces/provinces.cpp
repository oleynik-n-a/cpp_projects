#include "provinces.h"

#include <functional>
#include <iostream>
#include <queue>

int64_t CountPassports(const std::vector<int>& provinces) {
    int64_t passports = 0;
    std::priority_queue<int64_t, std::vector<int64_t>, std::greater<int64_t>> sorted_provinces;
    for (int i = 0; i < static_cast<int>(provinces.size()); ++i) {
        sorted_provinces.push(provinces[i]);
    }
    while (sorted_provinces.size() > 1) {
        int64_t a = sorted_provinces.top();
        sorted_provinces.pop();
        int64_t b = sorted_provinces.top();
        sorted_provinces.pop();
        passports += a + b;
        sorted_provinces.push(a + b);
    }
    return passports;
}
