#include <bits/stdc++.h>
#include "College.h"

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

    constexpr TestCourse EMPTY_COURSE = {"", false};
    constexpr int MAX_LEN = 10;
    constexpr int COURSES_TESTS = 199;
    set<TestCourse> courses;
    College instance;

    int gi(int lb, int ub) {
        static mt19937 rng(66643);
        return uniform_int_distribution<int>(lb, ub)(rng);
    }

    string gen_string(int len) {
        string name;

        for (int i = 0; i < len; ++i) {
            int type = gi(0, 10);
            if (type <= 5)
                name += (char) gi('a', 'z');
            else if (type <= 9)
                name += (char) gi('A', 'Z');
            else
                name += ' ';
        }

        return name;
    }

    bool validate_courses() {
        auto all_courses = instance.find_courses("*");
        if (courses.size() != all_courses.size())
            return false;

        for (shared_ptr<Course> &c : all_courses)
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
            TestCourse const& tc = random_course();
            courses.erase(tc);
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

    void init(int seed) {
        instance = College();
    }

    void assert_msg(bool expr, string const& msg) {
        if (!expr) {
            cerr << "Assertion failed: " << msg << endl;
            exit(1);
        }
    }
}

int main() {
    Tests::init(321312);
    for (int i = 0; i < Tests::COURSES_TESTS; i++) {
        Tests::assert_msg(Tests::perform_courses_op(), "Test " + to_string(i) + " failed");
    }
    Tests::validate_courses();

    cout << "OK" << endl;
}