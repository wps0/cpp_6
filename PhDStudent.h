#ifndef COLLEGE_PHDSTUDENT_H
#define COLLEGE_PHDSTUDENT_H


#include "Teacher.h"
#include "Student.h"

class PhDStudent : public Student, public Teacher {
public:
    PhDStudent(const std::string& name,
               const std::string& surname,
               bool active = true)
    : Person(name, surname)
    , Student(name, surname, active)
    , Teacher(name, surname) {}
};


#endif //COLLEGE_PHDSTUDENT_H
