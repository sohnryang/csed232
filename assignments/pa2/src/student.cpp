#include <student.hpp>

student::student() : dept(), name(), gender(), age(0) {}

student::student(const student &other)
    : dept(other.dept), name(other.name), gender(other.gender), age(other.age) {
}

student::student(std::string dept, std::string name, std::string gender,
                 int age)
    : dept(dept), name(name), gender(gender), age(age) {}

bool student::operator==(const student &other) const {
  return dept == other.dept && name == other.name && gender == other.gender &&
         age == other.age;
}

std::string student::get_label(category label_category) const {
  switch (label_category) {
  case category::DEPT:
    return dept;
  case category::GENDER:
    return gender;
  }
}

int student::get_value() const { return age; }
