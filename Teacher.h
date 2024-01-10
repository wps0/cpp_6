#ifndef COLLEGE_TEACHER_H
#define COLLEGE_TEACHER_H

#include <utility>

#include "Person.h"
#include "CoursesList.h"

class Teacher : public virtual Person {
private:
    CoursesList courses_;

public:
    Teacher(const std::string &name,
            const std::string &surname)
    : Person(name, surname) {}

    [[nodiscard]] std::vector<std::shared_ptr<Course>> get_courses() const {
        return courses_.get_values();
    }

    bool add_course(const std::shared_ptr<Course> &course) {
        return courses_.add(course);
    }
};


#endif //COLLEGE_TEACHER_H
