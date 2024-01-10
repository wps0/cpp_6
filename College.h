#ifndef COLLEGE_COLLEGE_H
#define COLLEGE_COLLEGE_H


#include "Course.h"

#include "Person.h"
#include "Student.h"
#include "Teacher.h"
#include "PhDStudent.h"

#include "MyList.h"
#include "CoursesList.h"
#include "PeopleList.h"

#include <string>
#include <unordered_map>

class College {
private:
    CoursesList courses_;
    PeopleList<Teacher> teachers_;
    PeopleList<Student> students_;
    PeopleList<PhDStudent> phd_students_;

    std::unordered_map<
            std::shared_ptr<Course>, PeopleList<Student>
    > course_students_;

    std::unordered_map<
            std::shared_ptr<Course>, PeopleList<Teacher>
    > course_teachers_;

    bool person_exists(const std::string &name, const std::string &surname);

public:
    // Dodaje przedmiot. Zwraca true, jeĹli przedmiot zostaĹ dodany, a false,
    // jeĹli istnieje juĹź przedmiot o tej samej nazwie.
    bool add_course(const std::string &name, bool active = true);

    // Wyszukuje przedmioty o nazwie pasującej do podanego wzorca. Wzorzec może
    // zawierać wieloznaczniki ? i *.
    std::vector<std::shared_ptr<Course>> find_courses(const std::string &pattern);

    // Zmienia status przedmiotu na aktywny lub nieaktywny zgodnie z podaną
    // wartością. Zwraca true, jeśli przedmiot istnieje, a false w przeciwnym
    // przypadku.
    bool change_course_activeness(const std::shared_ptr<Course> &course, bool active);

    // Usuwa przedmiot (z kolekcji przedmiotĂłw uczelni) i zmienia jego status
    // na nieaktywny. Zwraca true, jeśli istnieje przedmiot, lub false w przeciwnym
    // przypadku.
    bool remove_course(const std::shared_ptr<Course> &course);

    // Dodaje studenta, doktoranta lub nauczyciela. Typ T moĹźe być tylko Student,
    // PhDStudent lub Teacher. Trzeci parametr jest uwzględniany tylko wtedy, gdy
    // T nie jest Teacher. Zwraca true, jeśli osoba o podanych imieniu i nazwisku
    // została dodana, a false, jeśli już istnieje taka osoba.
    template <typename T>
        requires (std::is_same_v<T, Teacher>
                || std::is_same_v<T, Student>
                || std::is_same_v<T, PhDStudent>)
    bool add_person(const std::string &name,
                    const std::string &surname,
                    [[maybe_unused]] bool active = true);

    // Zmienia status studenta na aktywny lub nieaktywny zgodnie z podanÄ
    // wartoĹciÄ. Zwraca true, jeĹli student istnieje, a false w przeciwnym
    // przypadku.
    bool change_student_activeness(
            const std::shared_ptr<Student> &student,
            bool active
    );

    // Wyszukuje osoby o imieniu i nazwisku pasujÄcym do podanych wzorcĂłw.
    // Typ T moĹźe byÄ Person, Student, PhDStudent lub Teacher.
    // Wzorce mogÄ zawieraÄ wieloznaczniki ? i *.
    template <typename T>
    requires (std::is_same_v<T, Person>
              || std::is_same_v<T, Teacher>
              || std::is_same_v<T, Student>
              || std::is_same_v<T, PhDStudent>)
    std::vector<std::shared_ptr<T>> find(const std::string &name_pattern, const std::string &surname_pattern);

    // Wyszukuje studentĂłw zapisanych na podany przedmiot (jeśli T = Student)
    // lub nauczycieli prowadzÄcych podany przedmiot (jeśli T = Teacher).
    template <typename T>
    requires (std::is_convertible_v<T, Student>
                || std::is_convertible_v<T, Teacher>)
    std::vector<std::shared_ptr<T>> find(const std::shared_ptr<Course> &course);

    // Przypisuje przedmiot studentowi lub nauczycielowi zaleĹźnie od tego, czy
    // typ T jest to Student czy Teacher. Podnosi wyjątek przy prĂłbie przypisania
    // nieaktywnego przedmiotu lub nieaktywnemu studentowi. Podnosi rĂłwnieĹź
    // wyjÄtek, gdy dana osoba lub dany przedmiot nie istnieje.
    // Funkcja zwraca true, jeĹli przedmiot został przypisany studentowi lub
    // nauczycielowi, a false, jeĹli przedmiot był juĹź wcześniej przypisany.
    template <typename T>
    requires (std::is_convertible_v<T, Student>
              || std::is_convertible_v<T, Teacher>)
    bool assign_course(const std::shared_ptr<T> &, const std::shared_ptr<Course> &course);

};

#endif //COLLEGE_COLLEGE_H
