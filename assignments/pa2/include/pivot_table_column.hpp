#pragma once

#include <linked_list.hpp>

#include <string>

// pivot_table_column maintains data for one pivot table column.
class pivot_table_column {
private:
  // List of labels.
  list<std::string> labels;

  // List of values.
  list<int> values;

public:
  // Default constructor.
  pivot_table_column();

  // Copy constructor.
  pivot_table_column(const pivot_table_column &other);

  // Constructor with labels.
  pivot_table_column(const list<std::string> &labels);

  // Get maximum value of current column.
  int max_value() const;

  // Get minimum value of current column.
  int min_value() const;

  // Get average value of current column.
  float average_value() const;

  // Get labels of column.
  list<std::string> get_labels() const;

  // Append a value to this column.
  void append(int value);
};
