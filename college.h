#ifndef CPP_6_COLLEGE_H
#define CPP_6_COLLEGE_H

#include <string>
#include <vector>
#include <memory>

//namespace cxx {
    using std::string;

    class Course;

    class Person {
    public:
        Person(string name, string surname) noexcept;
        Person() = delete;
        string get_name() const noexcept;
        string get_surname() const noexcept;
    private:
        const string name, surname;
    };

    class Student : public virtual Person {
    public:
        Student(string name, string surname, bool active = true) noexcept;
        Student() = delete;
        bool is_active() const noexcept;
        auto get_courses() const;
    private:
        bool active;
        std::vector<std::shared_ptr<Course>> courses;
    };

    class Teacher : public virtual Person {
    public:
        Teacher(string name, string surname) noexcept;
        Teacher() = delete;
        auto get_courses() const;
    private:
        std::vector<std::shared_ptr<Course>> courses;
    };

    class PhDStudent : public Student, public Teacher {
    public:
        PhDStudent(string name, string surname) noexcept;
        PhDStudent() = delete;
    };

    class Course {
    public:
        Course(string name, bool active = true);
        Course() = delete;
        string get_name() const noexcept;
        bool is_active() const noexcept;
        template <typename T>
        void add_person(T p);

        bool operator==(Course const& other) const noexcept;
    private:
        string name;
        bool active;
        std::vector<shared_ptr<Student>> students;
        std::vector<shared_ptr<Teacher>> teachers;
    };

    class College {
    public:
        // Dodaje przedmiot. Zwraca true, jeśli przedmiot został dodany, a false,
        // jeśli istnieje już przedmiot o tej samej nazwie.
        bool add_course(string name, bool active = true);

        // Wyszukuje przedmioty o nazwie pasującej do podanego wzorca. Wzorzec może
        // zawierać wieloznaczniki ? i *.
        auto find_courses(string pattern);

        // Zmienia status przedmiotu na aktywny lub nieaktywny zgodnie z podaną
        // wartością. Zwraca true, jeśli przedmiot istnieje, a false w przeciwnym
        // przypadku.
        bool change_course_activeness(Course course, bool active);

        // Usuwa przedmiot (z kolekcji przedmiotów uczelni) i zmienia jego status
        // na nieaktywny. Zwraca true, jeśli istnieje przedmiot, lub false w przeciwnym
        // przypadku.
        bool remove_course(Course course);

        // Dodaje studenta, doktoranta lub nauczyciela. Typ T może być tylko Student,
        // PhDStudent lub Teacher. Trzeci parametr jest uwzględniany tylko wtedy, gdy
        // T nie jest Teacher. Zwraca true, jeśli osoba o podanych imieniu i nazwisku
        // została dodana, a false, jeśli już istnieje taka osoba.
        template<typename T>
        bool add_person(string name, string surname, bool active = true);

        // Zmienia status studenta na aktywny lub nieaktywny zgodnie z podaną
        // wartością. Zwraca true, jeśli student istnieje, a false w przeciwnym
        // przypadku.
        bool change_student_activeness(Student student, bool active);

        // Wyszukuje osoby o imieniu i nazwisku pasującym do podanych wzorców.
        // Typ T może być Person, Student, PhDStudent lub Teacher.
        // Wzorce mogą zawierać wieloznaczniki ? i *.
        template<typename T>
        auto find(string name_pattern, string surname_pattern);

        // Wyszukuje studentów zapisanych na podany przedmiot (jeśli T = Student)
        // lub nauczycieli prowadzących podany przedmiot (jeśli T = Teacher).
        template<typename T>
        auto find(Course course);

        // Przypisuje przedmiot studentowi lub nauczycielowi zależnie od tego, czy
        // typ T jest to Student czy Teacher. Podnosi wyjątek przy próbie przypisania
        // nieaktywnego przedmiotu lub nieaktywnemu studentowi. Podnosi również
        // wyjątek, gdy dana osoba lub dany przedmiot nie istnieje.
        // Funkcja zwraca true, jeśli przedmiot został przypisany studentowi lub
        // nauczycielowi, a false, jeśli przedmiot był już wcześniej przypisany.
        template<typename T>
        bool assign_course(Person person, Course course);
    };
//}

#endif //CPP_6_COLLEGE_H
