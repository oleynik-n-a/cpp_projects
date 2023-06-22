#pragma once

#include <algorithm>
#include <iostream>
#include <utility>

template <typename T>
class List {
private:
    class ListNode {
    public:
        friend class List;
        friend class Iterator;

    private:
        T* value_;
        ListNode* next_;
        ListNode* prev_;

        ListNode() : value_(nullptr), next_(this), prev_(this) {
        }

        explicit ListNode(T* value) : value_(value), next_(nullptr), prev_(nullptr) {
        }
    };

    void Unlink(ListNode* node) {
        if (node == head_) {
            return;
        }
        auto tmp_next = node->next_;
        auto tmp_prev = node->prev_;
        delete node->value_;
        delete node;
        tmp_next->prev_ = tmp_prev;
        tmp_prev->next_ = tmp_next;
        --size_;
    }

    void LinkAfter(ListNode* target, ListNode* after) {
        target->next_->prev_ = after;
        after->next_ = target->next_;
        target->next_ = after;
        after->prev_ = target;
        ++size_;
    }

    ListNode* head_;
    size_t size_;

public:
    class Iterator {
    private:
        ListNode* cur_;

    public:
        explicit Iterator(ListNode* cur) : cur_(cur) {
        }

        Iterator& operator++() {
            cur_ = cur_->next_;
            return *this;
        }

        Iterator operator++(int) {
            auto node = Iterator(cur_);
            cur_ = cur_->next_;
            return node;
        }

        Iterator& operator--() {
            cur_ = cur_->prev_;
            return *this;
        }

        Iterator operator--(int) {
            auto node = Iterator(*this);
            cur_ = cur_->prev_;
            return node;
        }

        T& operator*() const {
            return *cur_->value_;
        }

        T* operator->() const {
            return cur_;
        }

        bool operator==(const Iterator& rhs) const {
            return cur_ == rhs.cur_;
        }

        bool operator!=(const Iterator& rhs) const {
            return cur_ != rhs.cur_;
        }
    };

    List() {
        head_ = new ListNode();
        size_ = 0;
    }

    List(const List& list) {
        head_ = new ListNode();
        size_ = 0;

        ListNode* cur = list.head_->next_;
        while (list.head_ != cur) {
            PushBack(*cur->value_);
            cur = cur->next_;
        }
    }

    List(List&& list) {
        head_ = list.head_;
        size_ = list.size_;
        list.head_ = new ListNode();
        list.size_ = 0;
    }

    ~List() {
        while (!IsEmpty()) {
            PopBack();
        }
        delete head_;
    }

    List& operator=(const List& list) {
        List tmp(list);
        std::swap(head_, tmp.head_);
        std::swap(size_, tmp.size_);
        return *this;
    }

    List& operator=(List&& list) {
        std::swap(head_, list.head_);
        std::swap(size_, list.size_);
        return *this;
    }

    bool IsEmpty() const {
        return head_->next_ == head_;
    }

    size_t Size() const {
        return size_;
    }

    void PushBack(const T& elem) {
        LinkAfter(head_->prev_, new ListNode(new T(elem)));
    }

    void PushBack(T&& elem) {
        LinkAfter(head_->prev_, new ListNode(new T(std::move(elem))));
    }

    void PushFront(const T& elem) {
        LinkAfter(head_, new ListNode(new T(elem)));
    }

    void PushFront(T&& elem) {
        LinkAfter(head_, new ListNode(new T(std::move(elem))));
    }

    T& Front() {
        return *head_->next_->value_;
    }

    const T& Front() const {
        return *head_->next_->value_;
    }

    T& Back() {
        return *head_->prev_->value_;
    }

    const T& Back() const {
        return *head_->prev_->value_;
    }

    void PopBack() {
        Unlink(head_->prev_);
    }

    void PopFront() {
        Unlink(head_->next_);
    }

    Iterator Begin() {
        Iterator begin(head_->next_);
        return begin;
    }

    Iterator End() {
        Iterator end(head_);
        return end;
    }
};

template <typename T>
typename List<T>::Iterator begin(List<T>& list) {  // NOLINT
    return list.Begin();
}

template <typename T>
typename List<T>::Iterator end(List<T>& list) {  // NOLINT
    return list.End();
}
