#include "cstring.h"

size_t Strlen(const char* str) {
    size_t len = 0;
    while (str[len] != '\0') {
        ++len;
    }
    return len;
}

int Strcmp(const char* first, const char* second) {
    for (size_t i = 0; i < Strlen(first) && i < Strlen(second); ++i) {
        if (first[i] > second[i]) {
            return 1;
        }
        if (first[i] < second[i]) {
            return -1;
        }
    }
    if (Strlen(first) > Strlen(second)) {
        return 1;
    }
    if (Strlen(first) < Strlen(second)) {
        return -1;
    }
    return 0;
}

int Strncmp(const char* first, const char* second, size_t count) {
    if (count == 0) {
        return 0;
    }
    for (size_t i = 0; i < Strlen(first) && i < Strlen(second) && i < count; ++i) {
        if (first[i] > second[i]) {
            return 1;
        }
        if (first[i] < second[i]) {
            return -1;
        }
    }
    if (Strlen(first) > Strlen(second)) {
        return 1;
    }
    if (Strlen(first) < Strlen(second)) {
        return -1;
    }
    return 0;
}

char* Strcpy(char* dest, const char* src) {
    if (src == nullptr) {
        return dest;
    }
    for (size_t i = 0; i < Strlen(src); ++i) {
        dest[i] = src[i];
    }
    dest[Strlen(src)] = '\0';
    return dest;
}

char* Strncpy(char* dest, const char* src, size_t count) {
    if (src == nullptr) {
        return dest;
    }
    for (size_t i = 0; i < Strlen(src) && i < count; ++i) {
        dest[i] = src[i];
    }
    if (count > Strlen(src)) {
        for (size_t i = Strlen(src); i <= count; ++i) {
            dest[i] = '\0';
        }
    } else {
        dest[Strlen(src)] = '\0';
    }
    return dest;
}

char* Strcat(char* dest, const char* src) {
    char* end_point = &dest[Strlen(dest)];
    Strcpy(end_point, src);
    return dest;
}

char* Strncat(char* dest, const char* src, size_t count) {
    char* end_point = &dest[Strlen(dest)];
    Strncpy(end_point, src, count);
    return dest;
}

const char* Strchr(const char* str, char symbol) {
    const char* symbol_ptr = nullptr;
    for (size_t i = 0; i <= Strlen(str); ++i) {
        if (str[i] == symbol) {
            symbol_ptr = str + i;
            break;
        }
    }
    return symbol_ptr;
}

const char* Strrchr(const char* str, char symbol) {
    const char* symbol_ptr = nullptr;
    for (size_t i = Strlen(str) + 1; i > 0; --i) {
        if (str[i - 1] == symbol) {
            symbol_ptr = str + i - 1;
            break;
        }
    }
    return symbol_ptr;
}

size_t Strspn(const char* dest, const char* src) {
    size_t result = 0;
    for (size_t i = 0; i < Strlen(dest); ++i) {
        if (Strchr(src, dest[i]) != nullptr) {
            ++result;
        } else {
            break;
        }
    }
    return result;
}

size_t Strcspn(const char* dest, const char* src) {
    size_t result = 0;
    for (size_t i = 0; i < Strlen(dest); ++i) {
        if (Strchr(src, dest[i]) == nullptr) {
            ++result;
        } else {
            break;
        }
    }
    return result;
}

const char* Strpbrk(const char* dest, const char* breakset) {
    for (size_t i = 0; i < Strlen(breakset); ++i) {
        if (Strchr(dest, breakset[i]) != nullptr) {
            return dest + i;
        }
    }
    return nullptr;
}

const char* Strstr(const char* str, const char* pattern) {
    if (*pattern == '\0') {
        return str + Strlen(str);
    }
    for (size_t i = 0, j = 0; i <= Strlen(str); ++i) {
        if (str[i] == pattern[j]) {
            ++j;
        } else {
            i -= j;
            j = 0;
        }
        if (j == Strlen(pattern)) {
            return str + i - j + 1;
        }
    }
    return nullptr;
}
