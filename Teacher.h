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

    [[nodiscard]] std::set<std::shared_ptr<Course>, decltype(details::cmp_pnt)> get_courses() const {
        auto tmp = courses_.get_values();
        std::set<std::shared_ptr<Course>, decltype(details::cmp_pnt)> result;
        for (const auto &ptr: tmp)
            result.emplace(ptr);
        return result;
    }

    bool add_course(const std::shared_ptr<Course> &course) {
        return courses_.add(course);
    }
};


#endif //COLLEGE_TEACHER_H
