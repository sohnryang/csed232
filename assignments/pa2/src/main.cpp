#include <linked_list.hpp>
#include <pivot_table.hpp>
#include <pivot_table_column.hpp>
#include <student.hpp>

#include <cmath>
#include <iostream>
#include <string>

// command_type is an enum class for command types.
enum class command_type {
  ADD = 1,
  DELETE = 2,
  PRINT = 3,
  PIVOT = 4,
  EXIT = 5,
};

// input_with_retry gets input from stdin and retries inputs if
// check_input(input) is false, for cin failed to parse input.
template <typename T, typename F>
T input_with_retry(const std::string &prompt, const F &check_input) {
  while (true) {
    // Print the prompt.
    std::cout << prompt;

    // Declare a variable for user input.
    T result;

    // Read user input from stdin.
    std::cin >> result;

    // Clear the error state if the parse fails and ignore the rest of the input
    // until the next line break, with an error message.
    if (std::cin.fail()) {
      std::cin.clear();
      std::cin.ignore(1024, '\n');
      std::cout << "Parse failed" << std::endl;
      continue;
    }

    // Ignore the rest of the input until the next line break.
    std::cin.ignore(1024, '\n');

    // Check if the user input satisfies the predicate `check_input`.
    if (check_input(result))
      return result;

    // If the input doesn't satisfy the predicate `check_input`, prompt the user
    // to retry.
    std::cout << "Invalid input: " << result << std::endl;
  }
}

// input_line_with_retry gets a line from stdin and retries if
// check_input(input) is false.
template <typename F>
std::string input_line_with_retry(const std::string &prompt,
                                  const F &check_input) {
  while (true) {
    // Print the prompt.
    std::cout << prompt;

    // Declare a variable for user input.
    std::string result;

    // Read a line from stdin.
    std::getline(std::cin, result);

    // Check if the user input satisfies the predicate `check_input`.
    if (check_input(result))
      return result;

    // If the input doesn't satisfy the predicate `check_input`, prompt the user
    // to retry.
    std::cout << "Invalid input: " << result << std::endl;
  }
}

// input_student gets an input for student object.
student input_student(const list<std::string> &dept_list) {
  std::string dept, gender, name;
  int age;

  // Get department input from stdin with input validation
  dept = input_line_with_retry("Dept: ", [&dept_list](const std::string &s) {
    // Validate that all characters are uppercase letters
    for (const char &ch : s)
      if (ch < 'A' || ch > 'Z')
        return false;
    // If the department list is full, check if the input is in the list.
    if (dept_list.size() < 9)
      return true;
    return dept_list.search(s) != nullptr;
  });

  // Get gender input from stdin with input validation
  gender = input_line_with_retry(
      "Gender: ", [](const std::string &s) { return s == "F" || s == "M"; });

  // Get name input from stdin with input validation
  name = input_line_with_retry("Name: ", [](const std::string &s) {
    // Validate that there are no spaces in the name
    return s.find(" ") == std::string::npos;
  });

  // Get age input from stdin with input validation
  age = input_with_retry<int>("Age: ", [](int v) {
    return 18 <= v && v <= 30; // check if 18 <= age <= 30
  });

  // Create and return a student object with the collected input
  return student{dept, name, gender, age};
}

// input_command gets an input for command.
command_type input_command() {
  // Print the menu options
  std::cout << "----------MENU----------" << std::endl;
  std::cout << "1. Add a student" << std::endl;
  std::cout << "2. Delete a student" << std::endl;
  std::cout << "3. Print the student's list" << std::endl;
  std::cout << "4. Pivot Table" << std::endl;
  std::cout << "5. Exit" << std::endl;
  std::cout << "------------------------" << std::endl;

  // Prompt the user to select an option and validate their input
  int command_id = input_with_retry<int>(
      "Selection: ", [](int v) { return 1 <= v && v <= 5; });

  // Return the selected command as a command_type enum value
  return static_cast<command_type>(command_id);
}

// input_category gets an input for label types.
list<label_type> input_category() {
  // Display the menu options for category selection
  std::cout << "----------Category----------" << std::endl;
  std::cout << "1. Dept" << std::endl;
  std::cout << "2. Gender" << std::endl;
  std::cout << "3. Dept and Gender" << std::endl;
  std::cout << "----------------------------" << std::endl;

  // Get the user's category selection, ensuring that it is a valid option
  int category_id = input_with_retry<int>(
      "Selection: ", [](int v) { return 1 <= v && v <= 3; });

  list<label_type> result; // list to hold selected categories

  // If the first bit of category_id is set, add DEPT to the list
  if (category_id & 1)
    result.push_back(label_type::DEPT);

  // If the second bit of category_id is set, add GENDER to the list
  if (category_id & 2)
    result.push_back(label_type::GENDER);

  return result;
}

// input_function gets an input for pivot table function.
int input_function() {
  // Display the options available to the user.
  std::cout << "----------Function----------" << std::endl;
  std::cout << "1. Average" << std::endl;
  std::cout << "2. Max" << std::endl;
  std::cout << "3. Min" << std::endl;
  std::cout << "----------------------------" << std::endl;

  // Check the input is in [1, 3], and return the choice.
  return input_with_retry<int>("Selection: ",
                               [](int v) { return 1 <= v && v <= 3; });
}

// print_whole_table prints the list of students in sorted order.
void print_whole_table(const list<student> &list_to_print) {
  // Print the header row of the table.
  std::cout << "Dept\tGender\tName\tAge" << std::endl;

  // Use for_each to iterate over the list of students, and print each student's
  // information in a formatted row.
  for_each(list_to_print, [](const student &s) {
    std::cout << s.get_dept() << "\t" << s.get_gender() << "\t" << s.get_name()
              << "\t" << s.get_value() << std::endl;
  });
}

// collect_depts collects departments of student_list to a list of strings.
list<std::string> collect_depts(const list<student> &student_list) {
  // Create an empty list of department names to return
  list<std::string> depts;
  // For each student in the input list, add their department name to the output
  // list if it hasn't already been added
  for_each(student_list, [&depts](const student &s) {
    // Get the department name of the current student
    std::string dept = s.get_dept();
    // If the department name has already been added to the output list, skip to
    // the next student
    if (depts.search(dept))
      return;
    // Otherwise, add the department name to the output list
    depts.push_back(dept);
  });
  // Return the list of department names
  return depts;
}

int main() {
  // Initialize a boolean flag to keep track of when to exit the loop.
  bool finish = false;
  // Initialize list for storing students.
  list<student> student_list;
  // Start a loop until the finish flag is set to true.
  while (!finish) {
    // Get the user's input command.
    command_type command = input_command();
    // Switch statement to execute code based on the input command.
    switch (command) {
    case command_type::ADD: {
      // Collect list of departments.
      list<std::string> dept_list = collect_depts(student_list);
      // Get input for a new student.
      student new_student = input_student(dept_list);
      // Check if the student already exists.
      if (student_list.search(new_student) != nullptr)
        std::cout << "The student already exists." << std::endl;
      else {
        // If the student doesn't already exist, add them to the list and print
        // a message.
        student_list.push_back(new_student);
        std::cout << "A student is added in table!" << std::endl;
      }
      break;
    }
    case command_type::DELETE: {
      // Get input for the student to delete.
      student to_delete = input_student({});
      // Search for the node containing the student in the student list.
      auto node_to_delete = student_list.search(to_delete);
      // If the node isn't found, print a message indicating it couldn't be
      // deleted.
      if (node_to_delete == nullptr)
        std::cout << "Can't Delete it" << std::endl;
      else {
        // If the node is found, remove it from the list and print a message.
        student_list.remove(node_to_delete);
        std::cout << "Deleted!" << std::endl;
      }
      break;
    }
    case command_type::PRINT: {
      // Create a sorted list of students.
      list<student> sorted = sort(student_list);
      // Print the entire table of sorted students.
      print_whole_table(sorted);
      break;
    }
    case command_type::PIVOT: {
      // Get input for the label types and create a pivot table.
      list<label_type> label_types = input_category();
      pivot_table table(label_types);
      // Append each student to the pivot table.
      for_each(student_list, [&table](const student &s) { table.append(s); });
      // Sort the columns of the pivot table.
      list<pivot_table_column> columns = table.sorted();
      // Get input for the type of function to apply to the pivot table.
      int function_id = input_function();
      // Print the labels for each column of the pivot table.
      for_each(table.get_label_types(), [](label_type t) {
        if (t == label_type::DEPT)
          std::cout << "Dept";
        else
          std::cout << "Gender";
        std::cout << "\t";
      });
      // Print the label for caluclated value according to function_id.
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
        // Print tab-separated label values.
        for_each(col.get_labels(),
                 [](const std::string &label) { std::cout << label << "\t"; });
        // Print computed value.
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
      finish = true;                     // set finish flag as true
      std::cout << "Exit!" << std::endl; // print exit message
      break;
    }
  }
  return 0;
}
