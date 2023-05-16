#pragma once

template <typename T, typename U>
T FindFirst(T begin, T end, U value) {
    for (T i = begin; i < end; ++i) {
        if (*i == value) {
            return i;
        }
    }
    return end;
}

template <typename T, typename U>
T Remove(T begin, T end, U value) {
    T first = FindFirst(begin, end, value);
    for (T i = first + 1; i < end; ++i) {
        if (*i != value) {
            *first = *i;
            ++first;
        }
    }
    return first;
}
