#ifndef COURSES_LIST_H
#define COURSES_LIST_H

#include "MyList.h"
#include "Course.h"

class CoursesList : public MyList<Course> {
public:
    [[nodiscard]] std::vector<std::shared_ptr<Course>> find_courses(std::string pattern = "*") const;
};

#endif //COURSES_LIST_H
