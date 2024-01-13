cmake_minimum_required(VERSION 3.27)
project(College)

set(CMAKE_CXX_STANDARD 20)

add_executable(College main.cc
        CoursesList.h
        Person.h
        PhDStudent.h
        Student.h
        Teacher.h
        CoursesList.cc
        college.h
        College.cc
        PeopleList.h
        regex_helper.h
)


add_executable(CollegeTests tests.cc
        CoursesList.h
        Person.h
        PhDStudent.h
        Student.h
        Teacher.h
        CoursesList.cc
        college.h
        College.cc
        PeopleList.h
        regex_helper.h
)
