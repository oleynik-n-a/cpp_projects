#include "string_view.h"

#include <algorithm>

StringView::StringView() : string_(nullptr), size_(0) {
}

StringView::StringView(const char *source) {
    string_ = source;
    for (size_ = 0;; ++size_) {
        if (string_[size_] == '\0') {
            break;
        }
    }
}

StringView::StringView(const char *cstyle, size_t length) {
    string_ = cstyle;
    size_ = length;
}

char StringView::operator[](size_t idx) const {
    return *(string_ + idx);
}

char StringView::At(size_t idx) const {
    if (idx + 1 > size_) {
        throw StringViewOutOfRange{};
    }
    return *(string_ + idx);
}

char StringView::Front() const {
    return *string_;
}

char StringView::Back() const {
    return *(string_ + size_ - 1);
}

size_t StringView::Size() const {
    return size_;
}

size_t StringView::Length() const {
    return size_;
}

const char *StringView::Data() const {
    return string_;
}

bool StringView::Empty() const {
    return size_ == 0;
}

void StringView::Swap(StringView &other) {
    const char *tmp_string = other.string_;
    size_t tmp_size = other.size_;
    other.string_ = this->string_;
    other.size_ = this->size_;
    this->string_ = tmp_string;
    this->size_ = tmp_size;
}

void StringView::RemovePrefix(size_t prefix_size) {
    string_ = string_ + prefix_size;
    size_ -= prefix_size;
}

void StringView::RemoveSuffix(size_t suffix_size) {
    size_ -= suffix_size;
}

StringView StringView::Substr(size_t pos, size_t count) {
    if (pos + 1 > size_) {
        throw StringViewOutOfRange{};
    }
    int substr_length = std::min(count, size_ - pos);
    return StringView(string_ + pos, substr_length);
}
