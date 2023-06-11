#include "any.h"

#include <utility>

Any::Any() {
}

Any::Any(const Any &rhs) : ptr_(rhs.ptr_->Clone()) {
}

Any &Any::operator=(Any rhs) {
    this->Swap(rhs);
    return *this;
}

Any::~Any() {
    delete ptr_;
}

bool Any::Empty() const {
    return ptr_ == nullptr;
}

void Any::Clear() {
    delete ptr_;
    ptr_ = nullptr;
}

void Any::Swap(Any &rhs) {
    std::swap(ptr_, rhs.ptr_);
}
