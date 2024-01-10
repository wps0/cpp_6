#ifndef COLLEGE_PEOPLELIST_H
#define COLLEGE_PEOPLELIST_H

#include "MyList.h"
#include "Person.h"
#include "regex_helper.h"

#include <regex>

template<typename T> requires (std::is_convertible_v<T, Person>)
class PeopleList : public MyList<T> {
public:
    std::vector<std::shared_ptr<T>> find_people(
        std::string name_pattern = "*",
        std::string surname_pattern = "*"
    ) const;
};

template<class T> requires (std::is_convertible_v<T, Person>)
std::vector<std::shared_ptr<T>> PeopleList<T>::find_people(
        std::string name_pattern,
        std::string surname_pattern
) const {
    name_pattern = regex_helper::convert_regex(name_pattern);
    surname_pattern = regex_helper::convert_regex(surname_pattern);

    std::vector<std::shared_ptr<T>> result;
    const std::regex name_regex(name_pattern);
    const std::regex surname_regex(surname_pattern);

    for (const auto &person : this->values_) {
        if (std::regex_match(person->get_name(), name_regex) and
            std::regex_match(person->get_surname(), surname_regex))
            result.emplace_back(person);
    }

    return result;
}


#endif //COLLEGE_PEOPLELIST_H
