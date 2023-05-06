#pragma once

template <class Iterator, class T>
Iterator FindLast(Iterator first, Iterator last, const T& val) {
    for (Iterator i = last; i > first;) {
        if (*--i == val) {
            return i;
        }
    }
    return last;
}
