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

bool student::operator<(const student &other) const {
  // Check if comparision can be concluded from dept.
  if (dept < other.dept)
    return true;
  else if (dept > other.dept)
    return false;

  // Check if comparision can be concluded from gender.
  if (gender < other.gender)
    return true;
  else if (gender > other.gender)
    return false;

  // Check if comparision can be concluded from name.
  if (name < other.name)
    return true;
  else if (name > other.name)
    return false;

  // If other fields are the same, compare with age.
  return age < other.age;
}

std::string student::get_label(label_type label_category) const {
  switch (label_category) {
  case label_type::DEPT:
    return dept;
  default: // the remaining label is GENDER
    return gender;
  }
}

std::string student::get_dept() const { return dept; }

std::string student::get_gender() const { return gender; }

int student::get_value() const { return age; }

std::string student::get_name() const { return name; }
