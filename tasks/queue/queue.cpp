#include "queue.h"

Node::Node(int32_t value, Node* next) {
    this->value = value;
    this->next = next;
}

Queue::Queue() {
    size_ = 0;
    tail_ = new Node(0, 0);
    front_ = new Node(0, 0);
}

Queue::~Queue() {
    Clear();
    delete front_;
    delete tail_;
}

void Queue::Push(int32_t value) {
    if (size_ == 0) {
        front_->value = value;
        tail_->value = value;
    } else if (size_ == 1) {
        tail_->value = value;
        front_->next = tail_;
    } else {
        tail_->next = new Node(value, 0);
        tail_ = tail_->next;
    }
    ++size_;
}

void Queue::Pop() {
    if (!Empty()) {
        if (size_ > 2) {
            auto tmp = front_->next;
            delete front_;
            front_ = tmp;
        } else if (size_ == 2) {
            front_->value = tail_->value;
            front_->next = 0;
        } else {
            front_->value = 0;
            tail_->value = 0;
        }
        --size_;
    }
}

int32_t Queue::Front() const {
    return front_->value;
}

int32_t Queue::Size() const {
    return size_;
}

void Queue::Clear() {
    if (!Empty()) {
        while (size_ != 1) {
            auto tmp = front_->next;
            delete front_;
            front_ = tmp;
            --size_;
        }
        front_->value = 0;
        tail_->value = 0;
        --size_;
    }
}

bool Queue::Empty() const {
    return size_ == 0;
}
