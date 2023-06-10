#pragma once

template <typename T>
T Unique(T begin, T end) {
    T result = begin;
    *result = *begin;
    for (T iterator = begin; iterator < end; ++iterator) {
        if (*iterator > *result) {
            *(++result) = *iterator;
        }
    }
    return begin == end ? result : ++result;
}
