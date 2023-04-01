#include <linked_list.hpp>
#include <pivot_table.hpp>
#include <pivot_table_column.hpp>
#include <student.hpp>

#include <cmath>
#include <iostream>
#include <string>

enum class command_type {
  ADD = 1,
  DELETE = 2,
  PRINT = 3,
  PIVOT = 4,
  EXIT = 5,
};

void print_menu() {
  std::cout << "----------MENU----------" << std::endl;
  std::cout << "1. Add a student" << std::endl;
  std::cout << "2. Delete a student" << std::endl;
  std::cout << "3. Print the student's list" << std::endl;
  std::cout << "4. Pivot Table" << std::endl;
  std::cout << "5. Exit" << std::endl;
  std::cout << "------------------------" << std::endl;
}

student input_student() {
  std::string dept, gender, name;
  int age;
  std::cout << "Dept: ";
  std::cin >> dept;
  std::cout << "Gender: ";
  std::cin >> gender;
  std::cout << "Name: ";
  std::cin >> name;
  std::cout << "Age: ";
  std::cin >> age;
  student s(dept, name, gender, age);
  return s;
}

command_type input_command() {
  std::cout << "Selection: ";
  int command_id;
  std::cin >> command_id;
  return static_cast<command_type>(command_id);
}

list<label_type> input_category() {
  std::cout << "----------Category----------" << std::endl;
  std::cout << "1. Dept" << std::endl;
  std::cout << "2. Gender" << std::endl;
  std::cout << "3. Dept and Gender" << std::endl;
  std::cout << "----------------------------" << std::endl;
  while (true) {
    std::cout << "Selection: ";
    int category_id;
    std::cin >> category_id;
    list<label_type> result;
    if (category_id == 1) {
      result.push_back(label_type::DEPT);
      return result;
    } else if (category_id == 2) {
      result.push_back(label_type::GENDER);
      return result;
    } else if (category_id == 3) {
      result.push_back(label_type::DEPT);
      result.push_back(label_type::GENDER);
      return result;
    }
    std::cout << "Invalid input: " << category_id << std::endl;
  }
}

int input_function() {
  std::cout << "----------Function----------" << std::endl;
  std::cout << "1. Average" << std::endl;
  std::cout << "2. Max" << std::endl;
  std::cout << "3. Min" << std::endl;
  std::cout << "----------------------------" << std::endl;
  while (true) {
    std::cout << "Selection: ";
    int function_id;
    std::cin >> function_id;
    if (1 <= function_id && function_id <= 3)
      return function_id;
    std::cout << "Invalid input: " << function_id << std::endl;
  }
}

void print_whole_table(const list<student> &list_to_print) {
  std::cout << "Dept\tGender\tName\tAge" << std::endl;
  for_each(list_to_print, [](const student &s) {
    std::cout << s.get_label(label_type::DEPT) << "\t"
              << s.get_label(label_type::GENDER) << "\t" << s.get_name() << "\t"
              << s.get_value() << std::endl;
  });
}

int main() {
  bool finish = false;
  list<student> student_list;
  while (!finish) {
    print_menu();
    command_type command = input_command();
    switch (command) {
    case command_type::ADD: {
      student new_student = input_student();
      if (student_list.search(new_student) != nullptr)
        std::cout << "The student already exists." << std::endl;
      else {
        student_list.push_back(new_student);
        std::cout << "A student is added in table!" << std::endl;
      }
      break;
    }
    case command_type::DELETE: {
      student to_delete = input_student();
      auto node_to_delete = student_list.search(to_delete);
      if (node_to_delete == nullptr)
        std::cout << "Can't Delete it" << std::endl;
      else {
        student_list.remove(node_to_delete);
        std::cout << "Deleted!" << std::endl;
      }
      break;
    }
    case command_type::PRINT: {
      list<student> sorted =
          sort(student_list, [](const student &s1, const student &s2) {
            int dept_comparision = s1.get_label(label_type::DEPT)
                                       .compare(s2.get_label(label_type::DEPT)),
                gender_comparision =
                    s1.get_label(label_type::GENDER)
                        .compare(s2.get_label(label_type::GENDER)),
                name_comparision = s1.get_name().compare(s2.get_name()),
                age_comparision = s1.get_value() - s2.get_value();
            if (dept_comparision != 0)
              return dept_comparision;
            if (gender_comparision != 0)
              return gender_comparision;
            if (name_comparision != 0)
              return name_comparision;
            return age_comparision;
          });
      print_whole_table(sorted);
      break;
    }
    case command_type::PIVOT: {
      list<label_type> label_types = input_category();
      pivot_table table(label_types);
      for_each(student_list, [&table](const student &s) { table.append(s); });
      list<pivot_table_column> columns = table.sorted();
      int function_id = input_function();
      for_each(table.get_label_types(), [](label_type t) {
        if (t == label_type::DEPT)
          std::cout << "Dept";
        else
          std::cout << "Gender";
        std::cout << "\t";
      });
      switch (function_id) {
      case 1:
        std::cout << "Average";
        break;
      case 2:
        std::cout << "Max";
        break;
      case 3:
        std::cout << "Min";
        break;
      }
      std::cout << std::endl;
      for_each(columns, [function_id](const pivot_table_column &col) {
        for_each(col.get_labels(),
                 [](const std::string &label) { std::cout << label << "\t"; });
        switch (function_id) {
        case 1:
          std::cout << round(col.average_value() * 10) / 10;
          break;
        case 2:
          std::cout << col.max_value();
          break;
        case 3:
          std::cout << col.min_value();
          break;
        }
        std::cout << std::endl;
      });
      break;
    }
    case command_type::EXIT:
      finish = true;
      std::cout << "Exit!" << std::endl;
      break;
    }
  }
  return 0;
}
