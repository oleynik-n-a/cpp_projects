#pragma once

#include <utility>

template <typename Iterator>
void Reverse(Iterator begin, Iterator end) {
    for (Iterator iterator = begin; iterator < begin + (end - begin) / 2; ++iterator) {
        std::swap(*iterator, *(begin + (end - iterator - 1)));
    }
}

template <typename Iterator>
void Rotate(Iterator begin, Iterator mid, Iterator end) {
    Reverse(begin, mid);
    Reverse(mid, end);
    Reverse(begin, end);
}
