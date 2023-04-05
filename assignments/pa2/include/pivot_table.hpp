#pragma once

#include <linked_list.hpp>
#include <pivot_table_column.hpp>
#include <student.hpp>

// pivot_table holds multiple columns and maintains data for a pivot table.
class pivot_table {
private:
  // List of label types.
  list<label_type> label_types;

  // List of columns.
  list<pivot_table_column> columns;

public:
  // Default constructor.
  pivot_table(const pivot_table &other);

  // Copy constructor.
  pivot_table(const list<label_type> &label_types);

  // Append student data to the pivot table.
  void append(const student &data);

  // Return sorted list of pivot_table_column.
  list<pivot_table_column> sorted();

  // Get label types.
  list<label_type> get_label_types() const;
};
