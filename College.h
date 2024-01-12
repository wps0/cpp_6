#ifndef COLLEGE_COLLEGE_H
#define COLLEGE_COLLEGE_H


#include "Course.h"

#include "Person.h"
#include "Student.h"
#include "Teacher.h"
#include "PhDStudent.h"

#include "SharedPtrSet.h"
#include "CoursesList.h"
#include "PeopleList.h"

#include <string>
#include <unordered_map>
#include <set>

class College {
private:
    CoursesList courses_;
    PeopleList<Teacher> teachers_;
    PeopleList<Student> students_;

    std::unordered_map<
            std::shared_ptr<Course>, PeopleList<Student>
    > course_students_;

    std::unordered_map<
            std::shared_ptr<Course>, PeopleList<Teacher>
    > course_teachers_;

    bool person_exists(const std::string &name, const std::string &surname);

public:
    bool add_course(const std::string &name, bool active = true);

    // TODO: jak umiecie wywalić do .cpp żeby to łapało to to zróbcie XD
    std::set<std::shared_ptr<Course>, decltype(details::cmp_pnt)> find_courses(const std::string &pattern) {
        auto tmp = courses_.find_courses(pattern);
        std::set<std::shared_ptr<Course>, decltype(details::cmp_pnt)> result(details::cmp_pnt);
        for (const auto &ptr : tmp)
            result.emplace(ptr);
        return result;
    }

    bool change_course_activeness(const std::shared_ptr<Course> &course, bool active);

    bool remove_course(const std::shared_ptr<Course> &course);

    template <typename T>
        requires (std::is_same_v<T, Teacher>
                || std::is_same_v<T, Student>
                || std::is_same_v<T, PhDStudent>)
    bool add_person(const std::string &name,
                    const std::string &surname,
                    [[maybe_unused]] bool active = true);

    bool change_student_activeness(
            const std::shared_ptr<Student> &student,
            bool active
    );

    // TODO: jak umiecie wywalić do .cpp żeby to łapało to to zróbcie XD
    template <typename T>
    requires (std::is_same_v<T, Person>
              || std::is_same_v<T, Teacher>
              || std::is_same_v<T, Student>
              || std::is_same_v<T, PhDStudent>)
    std::set<std::shared_ptr<T>, decltype(details::cmp_pnt)> find(const std::string &name_pattern, const std::string &surname_pattern) {
        std::set<std::shared_ptr<T>, decltype(details::cmp_pnt)> result(details::cmp_pnt);
        if constexpr (std::is_base_of_v<Student, T> || std::is_base_of_v<T, Student>) {
            auto students = students_.find_people(name_pattern, surname_pattern);
            for (const auto &val : students) {
                auto tmp = std::dynamic_pointer_cast<T>(val);
                if (tmp != nullptr)
                    result.insert(tmp);
            }
        }

        if constexpr (std::is_base_of_v<T, Teacher>) { // T = Person or Teacher
            // unnecessary for PhDs, since they'll get caught by student search
            auto teachers = teachers_.find_people(name_pattern, surname_pattern);
            for (const auto &val : teachers) {
                auto tmp = std::dynamic_pointer_cast<T>(val);
                if (tmp != nullptr)
                    result.insert(tmp);
            }
        }
        return result;
    }

    template <typename T>
    requires (std::is_convertible_v<T, Student>
                || std::is_convertible_v<T, Teacher>)
    std::set<std::shared_ptr<T>> find(const std::shared_ptr<Course> &course);

    template <typename T>
    requires (std::is_convertible_v<T, Student>
              || std::is_convertible_v<T, Teacher>)
    bool assign_course(const std::shared_ptr<T> &person, const std::shared_ptr<Course> &course);

};

#endif //COLLEGE_COLLEGE_H
