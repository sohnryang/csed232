#pragma once

#include <linked_list.hpp>

#include <string>

class pivot_table_column {
private:
  list<std::string> labels;
  list<int> values;

public:
  pivot_table_column();
  pivot_table_column(const pivot_table_column &other);
  pivot_table_column(const list<std::string> &labels);

  int max_value() const;
  int min_value() const;
  float average_value() const;
  list<std::string> get_labels() const;
  void append(int value);
};
