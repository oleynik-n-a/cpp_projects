#pragma once

template <typename T, typename U>
U Copy(T src_begin, T src_end, U dest) {
    U result = dest;
    for (T iterator = src_begin; iterator < src_end;) {
        *result++ = *iterator++;
    }
    return result;
}

template <typename T, typename U>
U CopyBackward(T src_begin, T src_end, U dest) {
    U result = dest;
    for (T iterator = src_end; iterator > src_begin;) {
        *(--result) = *(--iterator);
    }
    return result;
}
