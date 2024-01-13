#include "college.h"

bool College::add_course(const std::string &name, bool active) {
    std::shared_ptr<Course> new_course = std::make_shared<Course>(name, active);
    return courses_.add(new_course);
}

// TODO: nie działa
/*std::set<std::shared_ptr<Course>, decltype(details::cmp_pnt)> College::find_courses(const std::string &pattern) {
    auto tmp = courses_.find_courses(pattern);
    std::set<std::shared_ptr<Course>, decltype(details::cmp_pnt)> result(details::cmp_pnt);
    for (const auto &ptr : tmp)
        result.emplace(ptr);
    return result;
}*/

bool College::change_course_activeness(const std::shared_ptr<Course> &course, bool active) {
    if (!courses_.contains(course))
        return false;
    course->set_active(active);
    return true;
}

bool College::remove_course(const std::shared_ptr<Course> &course) {
    if (!courses_.contains(course))
        return false;
    course->set_active(false);
    return courses_.remove(course);
}

template<>
bool College::add_person<Student>(const std::string &name, const std::string &surname, bool active) {
    if (person_exists(name, surname)) return false;
    return students_.add(std::make_shared<Student>(name, surname, active));
}
template<>
bool College::add_person<Teacher>(const std::string &name, const std::string &surname, [[maybe_unused]] bool active) {
    if (person_exists(name, surname)) return false;
    return teachers_.add(std::make_shared<Teacher>(name, surname));
}

template<>
bool College::add_person<PhDStudent>(const std::string &name, const std::string &surname, bool active) {
    if (person_exists(name, surname)) return false;
    auto phd_student = std::make_shared<PhDStudent>(name, surname, active);

    students_.add(phd_student);
    teachers_.add(phd_student);
    return true;
}

bool College::change_student_activeness(const std::shared_ptr<Student> &student, bool active) {
    if (!students_.contains(student))
        return false;

    student->set_active(active);
    return true;
}

// TODO: nie działa
/*template <typename T>
    requires (std::is_same_v<T, Person>
              || std::is_same_v<T, Teacher>
              || std::is_same_v<T, Student>
              || std::is_same_v<T, PhDStudent>)
    std::set<std::shared_ptr<T>, decltype(details::cmp_pnt)> College::find(const std::string &name_pattern, const std::string &surname_pattern) {
    std::set<std::shared_ptr<T>, decltype(details::cmp_pnt)> result(details::cmp_pnt);
    if constexpr (std::is_base_of_v<Student, T> || std::is_base_of_v<T, Student>) {
        auto students = students_.find_people(name_pattern, surname_pattern);
        for (const auto &val : students) {
            auto tmp = std::dynamic_pointer_cast<T>(val);
            if (tmp != nullptr)
                result.insert(tmp);
        }
    }

    if constexpr (std::is_base_of_v<T, Teacher>) {//(std::is_base_of_v<Teacher, T> || std::is_base_of_v<T, Teacher>) {
        auto teachers = teachers_.find_people(name_pattern, surname_pattern);
        for (const auto &val : teachers) {
            auto tmp = std::dynamic_pointer_cast<T>(val);
            if (tmp != nullptr)
                result.insert(tmp);
        }
    }
    return result;
}*/

template<>
std::set<std::shared_ptr<Teacher>> College::find<Teacher>(const std::shared_ptr<Course> &course) {
    return course_teachers_[course].get_values();
}

template<>
std::set<std::shared_ptr<Student>> College::find<Student>(const std::shared_ptr<Course> &course) {
    return course_students_[course].get_values();
}

template<>
bool College::assign_course<Student>(
        const std::shared_ptr<Student> &student,
        const std::shared_ptr<Course> &course
) {
    if (!course->is_active())
        throw std::runtime_error("Incorrect operation on an inactive course.");
    if (!courses_.contains(course))
        throw std::runtime_error("Non-existing course.");
    if (!students_.contains(student))
        throw std::runtime_error("Non-existing person.");
    if (!student->is_active())
        throw std::runtime_error("Incorrect operation for an inactive student.");

    student->add_course(course);
    return course_students_[course].add(student);
}

template<>
bool College::assign_course<Teacher>(
        const std::shared_ptr<Teacher> &teacher,
        const std::shared_ptr<Course> &course
) {
    if (!courses_.contains(course))
        throw std::runtime_error("Non-existing course.");
    if (!course->is_active())
        throw std::runtime_error("Incorrect operation on an inactive course.");
    if (!teachers_.contains(teacher))
        throw std::runtime_error("Non-existing person.");

    teacher->add_course(course);
    return course_teachers_[course].add(teacher);
}

bool College::person_exists(const std::string &name, const std::string &surname) {
    return !(find<Teacher>(name, surname).empty() and
             find<Student>(name, surname).empty());
}