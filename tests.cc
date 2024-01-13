#include <bits/stdc++.h>
#include "college.h"

using namespace std;

namespace Tests {
    struct TestCourse {
        string name;
        bool active;

        bool operator==(const TestCourse &rhs) const {
            return name == rhs.name &&
                   active == rhs.active;
        }

        bool operator!=(const TestCourse &rhs) const {
            return !(rhs == *this);
        }

        bool operator<(const TestCourse &rhs) const {
            if (name < rhs.name)
                return true;
            if (rhs.name < name)
                return false;
            return active < rhs.active;
        }

        bool operator>(const TestCourse &rhs) const {
            return rhs < *this;
        }

        bool operator<=(const TestCourse &rhs) const {
            return !(rhs < *this);
        }

        bool operator>=(const TestCourse &rhs) const {
            return !(*this < rhs);
        }
    };

    class GigaChadPhDStudent : public PhDStudent {
    public:
        GigaChadPhDStudent(const string &name, const string &surname,
                           bool active) : Person(name, surname), PhDStudent(name, surname, active) {}
    };

    struct TestPerson {
        string name, surname;
        int type;

        bool operator==(const TestPerson &rhs) const {
            return name == rhs.name &&
                   surname == rhs.surname;
        }

        bool operator!=(const TestPerson &rhs) const {
            return !(rhs == *this);
        }

        bool operator<(const TestPerson &rhs) const {
            if (name < rhs.name)
                return true;
            if (rhs.name < name)
                return false;
            if (surname < rhs.surname)
                return true;
            if (rhs.surname < surname)
                return false;
            return type < rhs.type;
        }

        bool operator>(const TestPerson &rhs) const {
            return rhs < *this;
        }

        bool operator<=(const TestPerson &rhs) const {
            return !(rhs < *this);
        }

        bool operator>=(const TestPerson &rhs) const {
            return !(*this < rhs);
        }
    };

    constexpr TestCourse EMPTY_COURSE = {"", false};
    constexpr TestPerson EMPTY_PERSON = {"", "", -1};
    constexpr int MAX_LEN = 10;
    constexpr int COURSES_TESTS = 20000;
    constexpr int PEOPLE_TESTS = 20000;
    constexpr int FIND_TESTS = 20000;
    set<TestCourse> courses;
    set<TestPerson> people;
    // person, course
    set<pair<string, string>> assignments;
    College instance;

    int gi(int lb, int ub) {
        static mt19937 rng(66643);
        return uniform_int_distribution<int>(lb, ub)(rng);
    }

    string gen_string(int len) {
        string name;

        for (int i = 0; i < len; ++i) {
            int type = gi(0, 14);
            if (type <= 5)
                name += (char) gi('a', 'z');
            else if (type <= 9)
                name += (char) gi('A', 'Z');
            else if (type <= 13)
                name += (char) gi('0', '9');
            else
                name += ' ';
        }

        return name;
    }

    bool validate_courses() {
        auto all_courses = instance.find_courses("*");
        if (courses.size() != all_courses.size())
            return false;

        for (shared_ptr<Course> const& c : all_courses)
            if (!courses.contains({c->get_name(), c->is_active()}))
                return false;
        return true;
    }

    TestCourse random_course() {
        if (!courses.empty()) {
            auto it = courses.begin();
            advance(it, gi(0, courses.size()-1));
            return *it;
        }

        return EMPTY_COURSE;
    }

    TestPerson random_person() {
        if (!courses.empty()) {
            auto it = people.begin();
            advance(it, gi(0, people.size()-1));
            return *it;
        }
        return EMPTY_PERSON;
    }

    string random_course_name() {
        if (gi(0, 2) == 0) {
            return random_course().name;
        }

        return gen_string(gi(1, MAX_LEN));
    }

    bool contains_course(TestCourse tc) {
        return courses.contains(tc) || courses.contains({tc.name, !tc.active});
    }

    bool perform_courses_op() {
        int op = gi(0, 99);
        bool expected = true, actual;
        if (courses.empty() || op < 40) {
            TestCourse tc = {random_course_name(), static_cast<bool>(gi(0, 1))};
            expected = !contains_course(tc);
            courses.insert(tc);
            actual = instance.add_course(tc.name, tc.active);
        } else if (op < 70) {
            TestCourse tc = random_course();
            assert(courses.erase(tc) == 1);
            courses.erase({tc.name, !tc.active});
//            cout << tc.name << endl;

            auto course_col = instance.find_courses(tc.name);
            actual = instance.remove_course(*course_col.begin());
        } else {
            TestCourse tc = random_course();
            courses.erase(tc);
            tc.active = !tc.active;
            courses.insert(tc);
            actual = instance.change_course_activeness(*instance.find_courses(tc.name).begin(), !tc.active);
        }

        return expected == actual;
    }

    bool perform_people_op() {
        int op = gi(0, 99);
        bool expected = true, actual;
        if (courses.empty() || people.empty() || op < 35) {
            string name = gen_string(MAX_LEN), surname = gen_string(MAX_LEN);
            int type = 0;

            if (op < 20) {
                actual = instance.add_person<Student>(name, surname);
            } else if (op < 30) {
                type = 1;
                actual = instance.add_person<PhDStudent>(name, surname);
            } else {
                type = 2;
                actual = instance.add_person<Teacher>(name, surname);
            }

            if (people.contains({name, surname, type}))
                expected = false;
        } else {
            TestPerson tp = random_person();
            TestCourse c = random_course();
            auto stud = instance.find<Student>(tp.name, tp.surname);
            auto ts = instance.find<Teacher>(tp.name, tp.surname);
            auto phds = instance.find<PhDStudent>(tp.name, tp.surname);
            auto found_courses = instance.find_courses(c.name);

            if (stud.empty() && ts.empty() && phds.empty()) {
                actual = false;
            } else if (!stud.empty()) {
                actual = instance.assign_course(*stud.begin(), *found_courses.begin());
            } else if (!phds.empty()) {
                if (gi(0, 2))
                    actual = instance.assign_course<Student>(*phds.begin(), *found_courses.begin());
                else
                    actual = instance.assign_course<Teacher>(*phds.begin(), *found_courses.begin());
            } else {
                actual = instance.assign_course(*ts.begin(), *found_courses.begin());
            }

            if (gi(0, 20) < 5) {
                if (!stud.empty())
                    instance.change_student_activeness(*stud.begin(), !stud.begin()->get()->is_active());
                else
                    instance.change_student_activeness(*stud.begin(), !phds.begin()->get()->is_active());
            }

            expected = !assignments.contains({tp.name + tp.surname, c.name});
        }

        return expected == actual;
    }

    void init(int seed) {
        instance = College();
    }

    void assert_msg(bool expr, string const& msg) {
        if (!expr) {
            cerr << "Assertion failed: " << msg << endl;
            exit(1);
        }
    }

    void test_courses() {
        cout << "Courses test: ";
        for (int i = 0; i < COURSES_TESTS; i++) {
            assert_msg(perform_courses_op(), "Test " + to_string(i) + " failed");
        }
        validate_courses();
        cout << "OK" << endl;
    }

    void test_people() {
        cout << "People test: ";
        for (int i = 0; i < PEOPLE_TESTS; i++) {
            assert_msg(perform_courses_op(), "Test " + to_string(i) + " failed");
        }
        validate_courses();
        cout << "OK" << endl;
    }

    void test_find() {
        cout << "Find tests: ";
    }

    void test_corner_cases() {
        cout << "Corner cases: ";

        College college{};

        // https://moodle.mimuw.edu.pl/mod/forum/discuss.php?d=9377#p20098 2)
        assert(college.add_person<PhDStudent>("Krzysztof", "Dix"));
        assert(college.add_person<Teacher>("Krzysztof", "Jakis"));
        assert(college.add_course("AIDS"));
        auto dix_phd = *college.find<PhDStudent>("K*", "?i?").begin();
        auto jakis_teacher = *college.find<Teacher>("*", "*").begin();
        shared_ptr<Course> algo_c = *college.find_courses("*").begin();

        assert_msg(college.find<PhDStudent>("*", "*").size() == 1,
                   "Actual size: " + to_string(college.find<Teacher>("*", "*").size()));

        assert(college.assign_course<Student>(dix_phd, algo_c));
        assert(college.assign_course<Teacher>(dix_phd, algo_c));
        assert(college.find<Teacher>(algo_c).size() == 1);
        assert(college.find<Student>(algo_c).size() == 1);

        // https://moodle.mimuw.edu.pl/mod/forum/discuss.php?d=9377#p20098 3)
        College college2{};
        assert(college2.add_course("AIDS"));
        assert(!college2.change_course_activeness(algo_c, false));
        assert(!college2.remove_course(algo_c));

        try {
            assert(!college2.assign_course<Teacher>(jakis_teacher, algo_c));
            assert(false);
        } catch (exception e) {}
        algo_c = *college2.find_courses("AIDS").begin();
        try {
            assert(!college2.assign_course<Teacher>(jakis_teacher, algo_c));
            assert(false);
        } catch (exception e) {}

        assert(college2.add_course("AISD"));

        assert(college2.find_courses("A???").size() == 2);
        assert(college2.find_courses("A*").size() == 2);
        assert(college2.find_courses("AISD*").size() == 1);
        assert(college2.find_courses("AI*SD").size() == 1);

        assert(college2.add_course("AnnD"));
        assert(college2.add_course("Annd"));
        assert(college2.find_courses("A???").size() == 4);
        assert(college2.find_courses("A*D").size() == 2);
        assert(college2.find_courses("A*???").size() == 4);
        assert(college2.find_courses("?*?*").size() == 4);
        assert(college2.find_courses("******?*?*").size() == 4);
        assert(college2.find_courses("******?*?*?????").empty());

        assert(college.find<PhDStudent>("*", "*").size() == 1);
        assert(college.find<PhDStudent>("Krzy*of", "D*").size() == 1);
        assert_msg(college.find<Teacher>("*", "*").size() == 2,
                   "Actual size: " + to_string(college.find<Teacher>("*", "*").size()));
        assert(college.find<Student>("*", "*").size() == 1);
        assert(college.find<Person>("*", "*").size() == 2);

        cout << "OK" << endl;
    }
}

int main() {
    Tests::init(321312);
    auto tests = {
            &Tests::test_corner_cases,
            &Tests::test_courses,
            &Tests::test_people
    };

    for (auto f : tests)
        f();
    cout << "All tests have passed!" << endl;
}