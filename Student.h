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

    [[nodiscard]] auto const& get_courses() const {
        return courses_.values_raw();
    }

    bool add_course(const std::shared_ptr<Course> &course) {
        return courses_.add(course);
    }
};


#endif //COLLEGE_STUDENT_H
