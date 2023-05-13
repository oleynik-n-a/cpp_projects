#pragma once

template <typename T>
T IsSortedUntil(T begin, T end) {
    for (T i = begin; i < end - 1; ++i) {
        if (*(i + 1) < *i) {
            return i + 1;
        }
    }
    return end;
}
