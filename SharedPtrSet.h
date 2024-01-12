#ifndef MY_LIST_H
#define MY_LIST_H

#include "Course.h"

#include <memory>
#include <set>

template<typename T>
class SharedPtrSet {
protected:
    static bool compare(
            const std::shared_ptr<T> &lhs, const std::shared_ptr<T> &rhs) {
        return *lhs < *rhs;
    }
    std::set<std::shared_ptr<T>, decltype(&compare)> values_;

public:
    SharedPtrSet() : values_(&compare) {}
    bool add(const std::shared_ptr<T> &val);
    bool remove(const std::shared_ptr<T> &val);
    bool contains(const std::shared_ptr<T> &val) const;
    std::set<std::shared_ptr<T>> get_values() const;
};

template<class T>
bool SharedPtrSet<T>::add(const std::shared_ptr<T> &value) {
    if (values_.contains(value))
        return false;
    values_.insert(value);
    return true;
}

template<class T>
bool SharedPtrSet<T>::remove(const std::shared_ptr<T> &value) {
    if (!values_.contains(value))
        return false;
    values_.erase(value);
    return true;
}

template<class T>
bool SharedPtrSet<T>::contains(const std::shared_ptr<T> &value) const {
    auto it = values_.find(value);
    return (it != values_.end() and *it == value);
}

template<class T>
std::set<std::shared_ptr<T>> SharedPtrSet<T>::get_values() const {
    std::set<std::shared_ptr<T>> result;
    for (auto &value : values_)
        result.emplace(value);
    return result;
}



#endif //MY_LIST_H
