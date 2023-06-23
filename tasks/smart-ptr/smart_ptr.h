#pragma once

#include <string>

struct Counter {
    size_t strong_count = 0;
    size_t weak_count = 0;

    Counter() = default;
};

template <class T>
class WeakPtr;

template <class T>
class SharedPtr {
private:
    T *ptr_ = nullptr;

public:
    Counter *counter_;

    explicit SharedPtr(const WeakPtr<T> &rhs);

    SharedPtr() {
        counter_ = new Counter();
    }

    explicit SharedPtr(T *x) {
        counter_ = new Counter();
        if (x != nullptr) {
            ++(counter_->strong_count);
        }
        ptr_ = x;
    }

    SharedPtr(const SharedPtr &x) {
        if (x.ptr_ == nullptr) {
            counter_ = new Counter;
        } else {
            counter_ = x.counter_;
            ++(counter_->strong_count);
        }
        ptr_ = x.ptr_;
    }

    SharedPtr(SharedPtr &&x) {
        ptr_ = x.ptr_;
        counter_ = x.counter_;
        x.ptr_ = nullptr;
        x.counter_ = new Counter();
    }

    SharedPtr &operator=(const SharedPtr &x) {
        if (counter_->strong_count != 0) {
            --(counter_->strong_count);
        }
        if (counter_->strong_count == 0) {
            delete ptr_;
            if (counter_->weak_count == 0) {
                delete counter_;
            }
        }

        if (x.ptr_ == nullptr) {
            counter_ = new Counter;
        } else {
            counter_ = x.counter_;
            ++(counter_->strong_count);
        }
        ptr_ = x.ptr_;
        return *this;
    }

    SharedPtr &operator=(SharedPtr &&x) {
        if (counter_->strong_count != 0) {
            --(counter_->strong_count);
        }
        if (counter_->strong_count == 0) {
            delete ptr_;
            if (counter_->weak_count == 0) {
                delete counter_;
            }
        }

        ptr_ = x.ptr_;
        counter_ = x.counter_;
        x.ptr_ = nullptr;
        x.counter_ = new Counter();
        return *this;
    }

    T *Get() {
        return ptr_;
    }

    T &operator*() {
        return *ptr_;
    }

    ~SharedPtr() {
        if (counter_->strong_count != 0) {
            --(counter_->strong_count);
        }
        if (counter_->strong_count == 0) {
            delete ptr_;
            if (counter_->weak_count == 0) {
                delete counter_;
            }
        }
    }

    void Reset(T *object) {
        --(counter_->strong_count);
        if (counter_->strong_count == 0) {
            delete ptr_;
            if (counter_->weak_count == 0) {
                delete counter_;
            }
        }

        counter_ = new Counter;
        if (object != nullptr) {
            ++(counter_->strong_count);
        }
        ptr_ = object;
    }
};

template <class T>
class WeakPtr {
private:
    T *ptr_ = nullptr;
    Counter *counter_ = nullptr;

public:
    SharedPtr<T> *shared = nullptr;

    WeakPtr() = default;

    WeakPtr(const WeakPtr &x) {
        if (x.ptr_ == nullptr) {
            counter_ = nullptr;
        } else {
            counter_ = x.counter_;
            ++(counter_->weak_count);
        }

        ptr_ = x.ptr_;
        shared = x.shared;
    }

    explicit WeakPtr(SharedPtr<T> &x) {
        if (x.Get() == nullptr) {
            counter_ = nullptr;
        } else {
            counter_ = x.counter_;
            ++(counter_->weak_count);
        }

        ptr_ = x.Get();
        shared = &x;
    }

    WeakPtr(WeakPtr &&x) {
        counter_ = x.ptr_ == nullptr ? nullptr : x.counter_;
        ptr_ = x.ptr_;
        shared = x.shared;
        x.ptr_ = nullptr;
    }

    WeakPtr &operator=(const WeakPtr &x) {
        if (counter_ != nullptr) {
            if (counter_->weak_count != 0) {
                --(counter_->weak_count);
            }
            if (counter_->strong_count == 0 && counter_->weak_count == 0) {
                delete counter_;
            }
        }

        if (x.ptr_ == nullptr) {
            counter_ = nullptr;
        } else {
            counter_ = x.counter_;
            ++(counter_->weak_count);
        }

        ptr_ = x.ptr_;
        shared = x.shared;
        return *this;
    }

    WeakPtr &operator=(WeakPtr &&x) {
        if (counter_ != nullptr) {
            if (counter_->weak_count != 0) {
                --(counter_->weak_count);
            }
            if (counter_->strong_count == 0 && counter_->weak_count == 0) {
                delete counter_;
            }
        }

        counter_ = x.ptr_ == nullptr ? nullptr : x.counter_;
        shared = x.shared;
        ptr_ = x.ptr_;
        x.ptr_ = nullptr;
        return *this;
    }

    ~WeakPtr() {
        if (counter_ != nullptr) {
            if (counter_->weak_count != 0) {
                --(counter_->weak_count);
            }
            if (counter_->strong_count == 0 && counter_->weak_count == 0) {
                delete counter_;
            }
        }
    }

    bool IsExpired() const {
        return ptr_ == nullptr || counter_->strong_count == 0 || counter_ == NULL;
    }

    SharedPtr<T> Lock() {
        if (IsExpired()) {
            return SharedPtr<T>();
        }
        return SharedPtr<T>(*this);
    }
};

template <class T>
SharedPtr<T>::SharedPtr(const WeakPtr<T> &rhs) {
    if (!(rhs.shared == nullptr || rhs.IsExpired())) {
        ptr_ = rhs.shared->ptr_;
        counter_ = rhs.shared->counter_;
        counter_->strong_count++;
    } else if (rhs.IsExpired()) {
        counter_ = new Counter;
        ptr_ = nullptr;
    } else {
        counter_ = new Counter;
        ptr_ = rhs.shared->ptr_;
    }
}
