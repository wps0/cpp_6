#ifndef COLLEGE_COURSE_H
#define COLLEGE_COURSE_H

#include <string>
#include <utility>

class Course {
private:
    std::string name_;
    bool active_;

public:
    explicit Course(std::string name, bool active = true)
        : name_(std::move(name)), active_(active) {}

    [[nodiscard]] std::string const& get_name() const {
        return name_;
    }

    [[nodiscard]] bool is_active() const {
        return active_;
    }

    void set_active(bool active) {
        active_ = active;
    }

    bool operator < (const Course &other) const {
        return name_ < other.name_;
    }
};

#endif //COLLEGE_COURSE_H
