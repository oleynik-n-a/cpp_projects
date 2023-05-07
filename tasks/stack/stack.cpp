#include "stack.h"

Node::Node(int32_t value, Node* previous) {
    this->value = value;
    this->previous = previous;
}

Stack::Stack() {
    size_ = 0;
    head_ = new Node(0, 0);
}

Stack::~Stack() {
    for (int32_t i = 0; i < size_; ++i) {
        auto tmp = head_->previous;
        delete head_;
        head_ = tmp;
    }
    delete head_;
}

void Stack::Push(int32_t value) {
    if (size_ == 0) {
        head_->value = value;
        size_ = 1;
    } else {
        head_ = new Node(value, head_);
        ++size_;
    }
}

void Stack::Pop() {
    if (size_ > 0) {
        auto tmp = head_->previous;
        delete head_;
        head_ = tmp;
        --size_;
    }
}

int32_t Stack::Top() const {
    return head_->value;
}

int32_t Stack::Size() const {
    return size_;
}

void Stack::Clear() {
    for (int32_t i = 0; i < size_; ++i) {
        auto tmp = head_->previous;
        delete head_;
        head_ = tmp;
    }
    delete head_;
    head_ = new Node(0, 0);
    size_ = 0;
}

bool Stack::Empty() const {
    return !size_;
}
