#pragma once

#include <functional>
#include <iterator>
#include <list>
#include <type_traits>
#include <utility>
#include <vector>

#define get_hash(key) std::hash<KeyT>{}(key)

template <typename KeyT>
class UnorderedSet {
public:
    UnorderedSet() {
    }

    explicit UnorderedSet(size_t count) {
        Reserve(count);
    }

    template <typename IteratorType,
              typename = std::enable_if_t<std::is_base_of_v<
                  std::forward_iterator_tag, typename std::iterator_traits<IteratorType>::iterator_category>>>
    UnorderedSet(IteratorType first, IteratorType last) {
        Reserve(std::distance(first, last));
        for (auto i = first; i != last; ++i) {
            Insert(*i);
        }
    }

    UnorderedSet(const UnorderedSet& other) : n_elements_(other.n_elements_), data_(other.data_) {
    }

    UnorderedSet(UnorderedSet&& other) : n_elements_(other.n_elements_), data_(std::move(other.data_)) {
        other.n_elements_ = 0;
    }

    ~UnorderedSet() {
    }

    UnorderedSet& operator=(const UnorderedSet& other) {
        n_elements_ = other.n_elements_;
        data_ = other.data_;
        return *this;
    }

    UnorderedSet& operator=(UnorderedSet&& other) {
        n_elements_ = other.n_elements_;
        other.n_elements_ = 0;
        data_ = std::move(other.data_);
        return *this;
    }

    size_t Size() const {
        return n_elements_;
    }

    bool Empty() const {
        return n_elements_ == 0;
    }

    void Clear() {
        n_elements_ = 0;
        data_.clear();
    }

    void Insert(const KeyT& key) {
        if (data_.size() <= n_elements_) {
            Rehash(data_.empty() ? 1 : 2 * data_.size());
        }
        data_[get_hash(key) % data_.size()].push_back(key);
        ++n_elements_;
    }

    void Insert(KeyT&& key) {
        if (data_.size() <= n_elements_) {
            Rehash(data_.empty() ? 1 : 2 * data_.size());
        }
        data_[get_hash(key) % data_.size()].push_back(key);
        ++n_elements_;
    }

    void Erase(const KeyT& key) {
        data_[get_hash(key) % data_.size()].remove(key);
        --n_elements_;
    }

    bool Find(const KeyT& key) const {
        if (data_.empty()) {
            return false;
        }
        auto cur_bucket = get_hash(key) % data_.size();
        for (auto i = data_[cur_bucket].begin(); i != data_[cur_bucket].end(); ++i) {
            if (*i == key) {
                return true;
            }
        }
        return false;
    }

    void Rehash(size_t new_bucket_count) {
        if (new_bucket_count < n_elements_) {
            return;
        }

        UnorderedSet tmp_set;
        tmp_set.data_.reserve(new_bucket_count);
        for (size_t i = 0; i < new_bucket_count; ++i) {
            tmp_set.data_.push_back(std::list<KeyT>());
        }
        if (!data_.empty()) {
            for (size_t i = 0; i < data_.size(); ++i) {
                for (auto iterator = data_[i].begin(); iterator != data_[i].end(); ++iterator) {
                    tmp_set.Insert(*iterator);
                }
            }
        }
        data_ = tmp_set.data_;
        n_elements_ = tmp_set.n_elements_;
    }

    void Reserve(size_t new_bucket_count) {
        if (new_bucket_count < data_.size()) {
            return;
        }
        size_t cur_size = data_.size();
        data_.reserve(new_bucket_count);
        for (size_t i = cur_size; i < new_bucket_count; ++i) {
            data_.push_back(std::list<KeyT>());
        }
    }

    size_t BucketCount() const {
        return data_.size();
    }

    size_t BucketSize(size_t id) const {
        return id < data_.size() ? data_[id].size() : 0;
    }

    size_t Bucket(const KeyT& key) const {
        return data_.empty() ? 0 : get_hash(key) % data_.size();
    }

    double LoadFactor() const {
        return data_.empty() ? 0 : static_cast<double>(n_elements_) / static_cast<double>(data_.size());
    }

private:
    size_t n_elements_ = 0;
    std::vector<std::list<KeyT>> data_;
};
