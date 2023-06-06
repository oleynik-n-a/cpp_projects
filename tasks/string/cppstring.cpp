#include "cppstring.h"

#include <cstring>

String::String() {
    size_ = 0;
    capacity_ = 0;
    data_ = nullptr;
}

String::String(size_t size, char symbol) {
    if (size != 0) {
        size_ = size;
        capacity_ = size_;
        data_ = new char[capacity_];
        for (size_t i = 0; i < size_; ++i) {
            data_[i] = symbol;
        }
    } else {
        size_ = 0;
        capacity_ = 0;
        data_ = nullptr;
    }
}

String::String(const char* src) {
    size_ = strlen(src);
    capacity_ = size_;
    data_ = new char[capacity_];
    for (size_t i = 0; i < size_; ++i) {
        data_[i] = src[i];
    }
}

String::String(const char* src, size_t size) {
    size_ = size;
    capacity_ = size_;
    data_ = new char[capacity_];
    for (size_t i = 0; i < size_ && i < strlen(src); ++i) {
        data_[i] = src[i];
    }
}

String::~String() {
    if (data_ != nullptr) {
        delete[] data_;
    }
}

String::String(const String& other) {
    if (other.data_ != nullptr) {
        size_ = other.size_;
        capacity_ = size_;
        data_ = new char[capacity_];
        for (size_t i = 0; i < size_; ++i) {
            data_[i] = other[i];
        }
    } else {
        size_ = 0;
        capacity_ = 0;
        data_ = nullptr;
    }
}

String& String::operator=(const String& other) {
    if (other.data_ != nullptr) {
        size_ = other.size_;
        capacity_ = size_;
        data_ = new char[capacity_];
        for (size_t i = 0; i < size_; ++i) {
            data_[i] = other[i];
        }
    } else {
        size_ = 0;
        capacity_ = 0;
        data_ = nullptr;
    }
    return *this;
}

const char& String::operator[](size_t idx) const {
    return data_[idx];
}

char& String::operator[](size_t idx) {
    return data_[idx];
}

const char& String::At(size_t idx) const {
    if (idx >= size_) {
        throw StringOutOfRange{};
    }
    return data_[idx];
}

char& String::At(size_t idx) {
    if (idx >= size_) {
        throw StringOutOfRange{};
    }
    return data_[idx];
}

const char& String::Front() const {
    return *data_;
}

char& String::Front() {
    return *data_;
}

const char& String::Back() const {
    return data_[size_ - 1];
}

char& String::Back() {
    return data_[size_ - 1];
}

const char* String::Data() const {
    return data_;
}

char* String::Data() {
    return data_;
}

const char* String::CStr() const {
    return data_;
}

char* String::CStr() {
    return data_;
}

bool String::Empty() const {
    return size_ == 0;
}

size_t String::Size() const {
    return size_ * sizeof(char);
}

size_t String::Length() const {
    return size_;
}

size_t String::Capacity() const {
    return capacity_;
}

void String::Clear() {
    size_ = 0;
    capacity_ = 0;
    data_ = nullptr;
}

void String::Swap(String& other) {
    auto tmp = other;
    other = *this;
    size_ = tmp.size_;
    capacity_ = tmp.capacity_;
    data_ = tmp.data_;
}

void String::PopBack() {
    if (size_ != 0) {
        --size_;
    }
}

void String::PushBack(char c) {
    if (Empty()) {
        ++size_;
        ++capacity_;
        data_ = new char[capacity_] { c };
    } else if (capacity_ > size_) {
        data_[size_++] = c;
    } else {
        auto tmp = data_;
        capacity_ *= 2;
        data_ = new char[capacity_];
        for (size_t i = 0; i < size_; ++i) {
            data_[i] = tmp[i];
        }
        data_[size_++] = c;
    }
}

void String::Resize(size_t new_size, char symbol) {
    if (new_size == 0) {
        size_ = 0;
        data_ = nullptr;
    } else {
        auto tmp = data_;
        capacity_ = new_size;
        data_ = new char[capacity_];
        for (size_t i = 0; i < capacity_; ++i) {
            data_[i] = i < size_ ? tmp[i] : symbol;
        }
        size_ = capacity_;
    }
}

void String::Reserve(size_t new_capacity) {
    capacity_ = new_capacity;
    auto tmp = data_;
    for (size_t i = 0; i < size_ && i < capacity_; ++i) {
        data_[i] = tmp[i];
    }
}

void String::ShrinkToFit() {
    capacity_ = size_;
    auto tmp = data_;
    for (size_t i = 0; i < size_; ++i) {
        data_[i] = tmp[i];
    }
}

int String::Compare(const String& other) const {
    for (size_t i = 0; i < size_ && i < other.size_; ++i) {
        if (data_[i] > other.data_[i]) {
            return 1;
        }
        if (data_[i] < other.data_[i]) {
            return -1;
        }
    }
    if (size_ > other.size_) {
        return 1;
    }
    if (size_ < other.size_) {
        return -1;
    }
    return 0;
}

String& String::operator+=(const String& other) {
    if (capacity_ == 0) {
        size_ = other.size_;
        capacity_ = other.capacity_;
        data_ = other.data_;
        return *this;
    }
    while (other.size_ + size_ > capacity_) {
        capacity_ *= 2;
    }
    auto tmp_data= data_;
    auto tmp_size = size_;
    size_ += other.size_;
    data_ = new char[capacity_];
    for (size_t i = 0; i < size_; ++i) {
        if (i < tmp_size) {
            data_[i] = tmp_data[i];
        } else {
            data_[i] = other.data_[i - tmp_size];
        }
    }
    return *this;
}

String operator+(const String& first, const String& second) {
    String result;
    result.size_ = first.size_ + second.size_;
    result.capacity_ = result.size_;
    result = new char[result.capacity_];
    for (size_t i = 0; i < result.size_; ++i) {
        if (i < first.size_) {
            result[i] = first[i];
        } else {
            result[i] = second[i - first.size_];
        }
    }
    return result;
}

std::ostream &operator<<(std::ostream& stream, const String& string) {
    for (size_t i = 0; i < string.Length(); ++i) {
        stream << string[i];
    }
    return stream;
}

bool operator==(const String& first, const String& second) {
    if (first.Empty() && second.Empty()) {
        return true;
    }
    return !first.Compare(second);
}

bool operator!=(const String& first, const String& second) {
    return !(first == second);
}

bool operator>(const String& first, const String& second) {
    if (first == second) {
        return false;
    }
    if (first.Compare(second) == 1) {
        return true;
    }
    return false;
}

bool operator<(const String& first, const String& second) {
    if (first == second) {
        return false;
    }
    return !(first > second);
}

bool operator>=(const String& first, const String& second) {
    return first > second || first == second;
}

bool operator<=(const String& first, const String& second) {
    return first < second || first == second;
}

void SafeCpy(char* dest, const char* src, size_t len) {
    dest = new char[len > strlen(src) ? len : strlen(src)];
    for (size_t i = 0; i < len && i < strlen(src); ++i) {
        dest[i] = src[i];
    }
}
