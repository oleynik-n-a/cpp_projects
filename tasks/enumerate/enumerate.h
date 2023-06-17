#pragma once

#include <iostream>

template<class Iterator>
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

template<class Iterator>
class RangeIterator {
private:
    size_t id_;
    Iterator cur_;

public:
    explicit RangeIterator(size_t id, Iterator cur) : id_(id), cur_(cur) {
    }

    RangeIterator& operator++() {
        ++id_;
        ++cur_;
        return *this;
    }

    std::pair<size_t, decltype(*cur_)> operator*() const {
        return {id_, *cur_};
    }

    bool operator!=(const RangeIterator& rhs) const {
        return cur_ != rhs.cur_;
    }
};

template<class Container>
auto Enumerate(Container& c) {
    return IteratorRange(RangeIterator(0, c.begin()), RangeIterator(std::distance(c.begin(), c.end()), c.end()));
}
