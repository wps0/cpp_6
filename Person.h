#ifndef COLLEGE_PERSON_H
#define COLLEGE_PERSON_H

#include <string>
#include <utility>

namespace details {
    inline static auto cmp_pnt = [](const auto &a, const auto &b) {
        return *a < *b;
    };
}

class Person {
protected:
    std::string name_;
    std::string surname_;

public:
    Person(std::string name, std::string surname)
        : name_(std::move(name)), surname_(std::move(surname)) {}

    virtual ~Person() = default;

    [[nodiscard]] std::string get_name() const {
        return name_;
    }

    [[nodiscard]] std::string get_surname() const {
        return surname_;
    }

    bool operator < (const Person &other) const {
        return std::pair(surname_, name_) < std::pair(other.surname_, other.name_);
    }
};


#endif //COLLEGE_PERSON_H
