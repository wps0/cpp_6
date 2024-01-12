#include "CoursesList.h"
#include "regex_helper.h"

#include <regex>

std::set<std::shared_ptr<Course>> CoursesList::find_courses(std::string pattern) const {
   pattern = regex_helper::convert_regex(pattern);

   std::set<std::shared_ptr<Course>> result;
   const std::regex regex(pattern);
   for (const auto &course : values_) {
       if (std::regex_match(course->get_name(), regex))
           result.emplace(course);
   }

    return result;
}