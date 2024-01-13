#ifndef COLLEGE_TEACHER_H
#define COLLEGE_TEACHER_H

#include "Person.h"
#include "CoursesList.h"

class Teacher : public virtual Person {
private:
    CoursesList courses_;

public:
    Teacher(const std::string &name,
            const std::string &surname)
    : Person(name, surname) {}

    [[nodiscard]] auto const& get_courses() const {
        return courses_.values_raw();
    }

    bool add_course(const std::shared_ptr<Course> &course) {
        return courses_.add(course);
    }
};


#endif //COLLEGE_TEACHER_H
