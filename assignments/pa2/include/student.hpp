#pragma once

#include <string>

class student {
private:
  std::string dept, name, gender;
  int age;

public:
  student();
  student(const student &other);
  student(std::string dept, std::string name, std::string gender, int age);
  void input_info();
  bool operator==(const student &other) const;
};
