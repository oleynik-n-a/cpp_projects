#pragma once

#include <memory>
#include <vector>
#include <string>

using std::string;

template <class T>
std::vector<std::unique_ptr<T>> Duplicate(const std::vector<std::shared_ptr<T>>& items) {
    std::vector<std::unique_ptr<T>> result;
    for (size_t i = 0; i < items.size(); ++i) {
        result.emplace_back(std::make_unique<T>(*items[i]));
    }
    return result;
}

template <class T>
std::vector<std::shared_ptr<T>> DeDuplicate(const std::vector<std::unique_ptr<T>>& items) {
    struct Comrapison {
        bool operator() (const std::shared_ptr<T>& l_ptr, const std::shared_ptr<T>& r_ptr) const{
            return *l_ptr < *r_ptr;
        }
    };

    std::set<std::shared_ptr<T>, Comrapison> pool;
    std::vector<std::shared_ptr<T>> result;
    for (size_t i = 0; i < items.size(); ++i) {
        auto copy = std::make_shared<T>(*items[i]);
        auto item = *pool.insert(copy).first;
        result.push_back(item);
    }
    return result;
}
