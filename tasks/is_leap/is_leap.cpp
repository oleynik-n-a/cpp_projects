#include "is_leap.h"

bool IsLeap(int year) {
    const int one = 100;
    const int four = 400;
    if ((year % 4 == 0 && year % one != 0) || (year % four == 0)) {
        return true;
    }
    return false;
}
