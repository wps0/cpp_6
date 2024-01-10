#ifndef MY_LIST_H
#define MY_LIST_H

#include "Course.h"

#include <memory>
#include <set>
#include <vector>

template<typename T>
class MyList {
protected:
    static bool compare(
            const std::shared_ptr<T> &lhs, const std::shared_ptr<T> &rhs) {
        return *lhs < *rhs;
    }
    std::set<std::shared_ptr<T>, decltype(&compare)> values_;

public:
    MyList() : values_(&compare) {}
    bool add(const std::shared_ptr<T> &val);
    bool remove(const std::shared_ptr<T> &val);
    bool contains(const std::shared_ptr<T> &val) const;
    std::vector<std::shared_ptr<T>> get_values() const;
};

template<class T>
bool MyList<T>::add(const std::shared_ptr<T> &value) {
    if (values_.contains(value))
        return false;
    values_.insert(value);
    return true;
}

template<class T>
bool MyList<T>::remove(const std::shared_ptr<T> &value) {
    if (!values_.contains(value))
        return false;
    values_.erase(value);
    return true;
}

template<class T>
bool MyList<T>::contains(const std::shared_ptr<T> &value) const {
    auto it = values_.find(value);
    return (it != values_.end() and *it == value);
}

template<class T>
std::vector<std::shared_ptr<T>> MyList<T>::get_values() const {
    std::vector<std::shared_ptr<T>> result;
    result.reserve(values_.size());
    for (auto &value : values_)
        result.emplace_back(value);
    return result;
}



#endif //MY_LIST_H
