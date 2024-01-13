#ifndef COLLEGE_STUDENT_H
#define COLLEGE_STUDENT_H

#include "Person.h"
#include "CoursesList.h"
#include "Course.h"

class Student : public virtual Person {
private:
    bool active_;
    CoursesList courses_;

public:
    Student(const std::string &name,
            const std::string &surname,
            bool active = true)
    : Person(name, surname), active_(active) {}

    [[nodiscard]] bool is_active() const noexcept {
        return active_;
    }

    void set_active(bool active) noexcept {
        active_ = active;
    }

    [[nodiscard]] std::set<std::shared_ptr<Course>, decltype(details::cmp_pnt)> get_courses() const {
        const auto tmp = courses_.get_values();
        std::set<std::shared_ptr<Course>, decltype(details::cmp_pnt)> result;
        for (const auto &ptr: tmp)
            result.emplace(ptr);
        return result;
    }

    bool add_course(const std::shared_ptr<Course> &course) {
        return courses_.add(course);
    }
};


#endif //COLLEGE_STUDENT_H
