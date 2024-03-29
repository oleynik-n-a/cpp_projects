#pragma once

#include <utility>

template <class Iterator>
class IteratorRange {
public:
    IteratorRange(Iterator begin, Iterator end) : begin_(begin), end_(end) {
    }

    Iterator begin() const {  // NOLINT
        return begin_;
    }

    Iterator end() const {  // NOLINT
        return end_;
    }

private:
    Iterator begin_, end_;
};

template <class T>
class RangeIterator {
public:
    RangeIterator(T cur, T step) : cur_(cur), step_(step) {
    }

    RangeIterator& operator++() {
        cur_ += step_;
        return *this;
    }

    T operator*() const {
        return cur_;
    }

    bool operator!=(const RangeIterator& rhs) const {
        return cur_ < rhs.cur_;
    }

private:
    T cur_;
    T step_;
};

template <class T>
auto Range(T from, T to, T step) {
    return IteratorRange(RangeIterator(from, step), RangeIterator(to, step));
}

template <class T>
auto Range(T from, T to) {
    return Range(from, to, T{1});
}

template <class T>
auto Range(T to) {
    return Range(T{0}, to);
}

template <class LeftIterator, class RightIterator>
class ZipIterator {
public:
    ZipIterator(LeftIterator first, RightIterator second) : first_(first), second_(second) {
    }

    ZipIterator& operator++() {
        ++first_;
        ++second_;
        return *this;
    }

    auto operator*() const {
        return std::make_pair(*first_, *second_);
    }

    bool operator!=(const ZipIterator& rhs) const {
        return first_ != rhs.first_ && second_ != rhs.second_;
    }

private:
    LeftIterator first_;
    RightIterator second_;
};

template <class L, class R>
auto Zip(const L& left, const R& right) {
    return IteratorRange(ZipIterator(left.begin(), right.begin()), ZipIterator(left.end(), right.end()));
}

template <class Iterator>
class GroupIterator {
public:
    GroupIterator(Iterator cur, Iterator end) : cur_(cur), end_(end) {
    }

    GroupIterator& operator++() {
        auto prev = cur_;
        for (;;) {
            ++cur_;
            if (cur_ == end_ || *cur_ != *prev) {
                break;
            }
        }
        return *this;
    }

    auto operator*() {
        Iterator next = cur_;
        while (next != end_ && *next == *cur_) {
            ++next;
        }
        return IteratorRange(cur_, next);
    }

    bool operator!=(const GroupIterator& rhs) const {
        return cur_ != rhs.cur_;
    }

private:
    Iterator cur_;
    Iterator end_;
};

template <class C>
auto Group(const C& data) {
    return IteratorRange(GroupIterator(data.begin(), data.end()), GroupIterator(data.end(), data.end()));
}
