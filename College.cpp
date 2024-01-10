#include "College.h"

bool College::add_course(const std::string &name, bool active) {
    std::shared_ptr<Course> new_course = std::make_shared<Course>(name, active);
    return courses_.add(new_course);
}

std::vector<std::shared_ptr<Course>>College::find_courses(const std::string &pattern) {
    return courses_.find_courses(pattern);
}

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

    bool ret = phd_students_.add(phd_student);
    if (!ret) return false;

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


template<> std::vector<std::shared_ptr<Person>> College::find<Person>(
        const std::string &name_pattern,
        const std::string &surname_pattern
) {
    auto students = students_.find_people(name_pattern, surname_pattern);
    auto teachers = teachers_.find_people(name_pattern, surname_pattern);

    std::vector<std::shared_ptr<Person>> result;
    for (const auto &val : students)
        result.emplace_back(val);
    for (const auto &val : teachers)
        result.emplace_back(val);

    std::sort(result.begin(), result.end(), [](const auto &a, const auto &b) {
        return *a < *b;
    });
    auto equal = [](const auto &a, const auto &b) {
        return a->get_name() == b->get_name() and
               a->get_surname() == b->get_surname();
    };
    result.erase(std::unique(result.begin(), result.end(), equal), result.end());
    return result;
}

template<> std::vector<std::shared_ptr<Student>> College::find<Student>(
        const std::string &name_pattern,
        const std::string &surname_pattern
) {
    return students_.find_people(name_pattern, surname_pattern);
}

template<> std::vector<std::shared_ptr<Teacher>> College::find<Teacher>(
        const std::string &name_pattern,
        const std::string &surname_pattern
) {
    return teachers_.find_people(name_pattern, surname_pattern);
}

template<> std::vector<std::shared_ptr<PhDStudent>> College::find<PhDStudent>(
        const std::string &name_pattern,
        const std::string &surname_pattern
) {
    return phd_students_.find_people(name_pattern, surname_pattern);
}

template<>
std::vector<std::shared_ptr<Teacher>> College::find<Teacher>(const std::shared_ptr<Course> &course) {
    return course_teachers_[course].get_values();
}

template<>
std::vector<std::shared_ptr<Student>> College::find<Student>(const std::shared_ptr<Course> &course) {
    return course_students_[course].get_values();
}

template<>
bool College::assign_course<Student>(
        const std::shared_ptr<Student> &student,
        const std::shared_ptr<Course> &course
) {
    //TODO: proper exceptions
    if (!students_.contains(student) or !student->is_active())
        throw std::runtime_error("Student is inactive or does not exist.");
    if (!courses_.contains(course) or !course->is_active())
        throw std::runtime_error("Course is inactive or does not exist.");

    student->add_course(course);
    return course_students_[course].add(student);
}

template<>
bool College::assign_course<Teacher>(
        const std::shared_ptr<Teacher> &teacher,
        const std::shared_ptr<Course> &course
) {
    //TODO: proper exceptions
    if (!teachers_.contains(teacher))
        throw std::runtime_error("Teacher does not exist.");
    if (!courses_.contains(course) or !course->is_active())
        throw std::runtime_error("Course is inactive or does not exist.");

    teacher->add_course(course);
    return course_teachers_[course].add(teacher);
}

bool College::person_exists(const std::string &name, const std::string &surname) {
    return !(find<Teacher>(name, surname).empty() and
             find<Student>(name, surname).empty());
}
