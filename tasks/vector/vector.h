#pragma once

template <class T>
class Vector {
public:
    Vector() {
        capacity_ = 1;
        data_ = new T[capacity_];
    }

    explicit Vector(size_t size) {
        size_ = size;
        capacity_ = size_;
        data_ = new T[capacity_]{};
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
