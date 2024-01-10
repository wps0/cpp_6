cmake_minimum_required(VERSION 3.27)
project(College)

set(CMAKE_CXX_STANDARD 20)

add_executable(College main.cpp
        CoursesList.h
        Person.h
        PhDStudent.h
        Student.h
        Teacher.h
        CoursesList.cpp
        College.h
        College.cpp
        PeopleList.h
        regex_helper.h
)
