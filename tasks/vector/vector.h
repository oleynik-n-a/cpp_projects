#pragma once

#include <algorithm>
#include <initializer_list>
#include <iterator>

template <class T>
class Vector {
public:
    Vector() {
        Reserve(1);
    }

    explicit Vector(size_t size) {
        Reserve(size);
        for (size_t i = 0; i < size; ++i) {
            PushBack(0);
        }
    }

    Vector(std::initializer_list<T> list) {
        auto first = list.begin();
        auto last = list.end();
        Reserve(std::distance(first, last));
        while (first != last) {
            PushBack(*first);
            ++first;
        }
    }

    Vector(const Vector& rhs) {
        Reserve(rhs.Size());
        for (size_t i = 0; i < rhs.Size(); ++i) {
            PushBack(rhs[i]);
        }
    }

    Vector(Vector&& rhs) {
        data_ = rhs.data_;
        size_ = rhs.size_;
        capacity_ = rhs.capacity_;
        rhs.data_ = nullptr;
    }

    Vector& operator=(Vector rhs) {
        Swap(rhs);
        return *this;
    }

    ~Vector() {
        delete[] data_;
    }

    void Swap(Vector& rhs) {
        std::swap(data_, rhs.data_);
        std::swap(size_, rhs.size_);
        std::swap(capacity_, rhs.capacity_);
    }

    void Reserve(size_t size) {
        if (size == 0) {
            size = 1;
        }
        if (size <= Capacity()) {
            return;
        }
        Realloc(size);
    }

    void PushBack(T value) {
        if (size_ == capacity_) {
            Realloc(capacity_ * 2);
        }
        data_[size_++] = value;
    }

    void PopBack() {
        --size_;
    }

    T& operator[](size_t ind) {
        return data_[ind];
    }

    T operator[](size_t ind) const {
        return data_[ind];
    }

    size_t Size() const {
        return size_;
    }

    size_t Capacity() const {
        return capacity_;
    }

    void Clear() {
        size_ = 0;
    }

    class Iterator {
    public:
        Iterator() {
        }

        explicit Iterator(T* cur) : cur_(cur) {
        }

        Iterator& operator+=(ssize_t diff) {
            cur_ += diff;
            return *this;
        }

        Iterator operator+(ssize_t diff) const {
            Iterator result(*this);
            return result += diff;
        }

        Iterator& operator-=(ssize_t diff) {
            cur_ -= diff;
            return *this;
        }

        Iterator operator-(ssize_t diff) const {
            Iterator result(*this);
            return result -= diff;
        }

        ssize_t operator-(const Iterator& rhs) const {
            return cur_ - rhs.cur_;
        }

        Iterator& operator++() {
            return *this += 1;
        }

        Iterator operator++(int) {
            Iterator tmp(*this);
            ++(*this);
            return tmp;
        }

        Iterator& operator--() {
            return *this -= 1;
        }

        Iterator operator--(int) {
            Iterator tmp(*this);
            --(*this);
            return tmp;
        }

        bool operator==(const Iterator& rhs) const {
            return cur_ == rhs.cur_;
        }

        bool operator!=(const Iterator& rhs) const {
            return cur_ != rhs.cur_;
        }

        T& operator*() {
            return *cur_;
        }

        T* operator->() {
            return cur_;
        }

    private:
        T* cur_;
    };

    Iterator begin() {  // NOLINT
        return Iterator(data_);
    }

    Iterator end() {  // NOLINT
        return Iterator(data_ + size_);
    }

    Iterator Begin() {
        return begin();
    }

    Iterator End() {
        return end();
    }

private:
    T* data_ = nullptr;
    size_t size_ = 0;
    size_t capacity_ = 0;

    void Realloc(size_t new_size) {
        if (data_ == nullptr) {
            data_ = new T[new_size];
            capacity_ = new_size;
            return;
        }
        T* new_data = new T[new_size];
        std::move(data_, data_ + size_, new_data);
        capacity_ = new_size;
        delete[] data_;
        data_ = new_data;
    }
};
