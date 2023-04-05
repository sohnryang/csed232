#pragma once

#include <string>

// label_type holds data for label types.
enum class label_type { DEPT, GENDER };

// student class holds data for a student.
class student {
private:
  // Field for department, name, and gender.
  std::string dept, name, gender;
  // Field for age of the student.
  int age;

public:
  // Default constructor.
  student();

  // Copy constructor.
  student(const student &other);

  // Constructor with data arguments.
  student(std::string dept, std::string name, std::string gender, int age);

  // Overloaded equality operator for checking equality.
  bool operator==(const student &other) const;

  // Overloaded less-than operator for comparision.
  bool operator<(const student &other) const;

  // Get labels with corresponding label type.
  std::string get_label(label_type label_category) const;

  // Getter for department.
  std::string get_dept() const;

  // Getter for gender.
  std::string get_gender() const;

  // Getter for age.
  int get_value() const;

  // Getter for name.
  std::string get_name() const;
};
