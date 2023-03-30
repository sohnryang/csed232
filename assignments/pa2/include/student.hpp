#pragma once

#include <string>

enum class category { DEPT, GENDER };

class student {
private:
  std::string dept, name, gender;
  int age;

public:
  student();
  student(const student &other);
  student(std::string dept, std::string name, std::string gender, int age);

  bool operator==(const student &other) const;
  std::string get_label(category label_category) const;
  int get_value() const;
};
