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
        capacity_ = 2 * size_;
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
    capacity_ = 2 * size_;
    data_ = new char[capacity_];
    for (size_t i = 0; i < size_; ++i) {
        data_[i] = src[i];
    }
}

String::String(const char* src, size_t size) {
    size_ = size;
    capacity_ = 2 * size_;
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
        capacity_ = other.capacity_;
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
    delete[] data_;
    if (other.data_ != nullptr) {
        size_ = other.size_;
        capacity_ = 2 * size_;
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
}

void String::Swap(String& other) {
    auto tmp_size = other.size_;
    auto tmp_capacity = other.capacity_;
    auto tmp_data = other.data_;
    other.size_ = size_;
    other.capacity_ = capacity_;
    other.data_ = data_;
    size_ = tmp_size;
    capacity_ = tmp_capacity;
    data_ = tmp_data;
}

void String::PopBack() {
    if (size_ != 0) {
        --size_;
    }
}

void String::PushBack(char c) {
    if (capacity_ == 0) {
        ++size_;
        capacity_ += 2;
        delete[] data_;
        data_ = new char[capacity_]{c};
    } else if (capacity_ > size_) {
        data_[size_++] = c;
    } else {
        Reserve(2 * capacity_);
        data_[size_++] = c;
    }
}

void String::Resize(size_t new_size, char symbol) {
    if (new_size == 0) {
        size_ = 0;
        delete[] data_;
        data_ = nullptr;
    } else {
        auto tmp = data_;
        capacity_ = new_size;
        data_ = new char[capacity_];
        for (size_t i = 0; i < capacity_; ++i) {
            data_[i] = i < size_ ? tmp[i] : symbol;
        }
        size_ = capacity_;
        delete[] tmp;
    }
}

void String::Reserve(size_t new_capacity) {
    if (new_capacity > capacity_) {
        auto tmp = data_;
        data_ = new char[new_capacity];
        for (size_t i = 0; i < size_; ++i) {
            data_[i] = tmp[i];
        }
        capacity_ = new_capacity;
        delete[] tmp;
    }
}

void String::ShrinkToFit() {
    capacity_ = size_;
    auto tmp = data_;
    data_ = new char[size_];
    for (size_t i = 0; i < size_; ++i) {
        data_[i] = tmp[i];
    }
    delete[] tmp;
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
        data_ = new char[capacity_];
        for (size_t i = 0; i < capacity_; ++i) {
            data_[i] = other[i];
        }
        return *this;
    }
    if (capacity_ < size_ + other.size_) {
        Reserve(2 * (size_ + other.size_));
    }
    for (size_t i = 0; i < other.size_; ++i) {
        PushBack(other[i]);
    }
    return *this;
}

String operator+(const String& first, const String& second) {
    String result = first;
    return result += second;
}

std::ostream& operator<<(std::ostream& stream, const String& string) {
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
    for (size_t i = 0; i < len; ++i) {
        dest[i] = src[i];
    }
}
