#ifndef COURSES_LIST_H
#define COURSES_LIST_H

#include "SharedPtrSet.h"
#include "Course.h"

class CoursesList : public SharedPtrSet<Course> {
public:
    [[nodiscard]] std::set<std::shared_ptr<Course>> find_courses(std::string pattern) const;
};

#endif //COURSES_LIST_H
