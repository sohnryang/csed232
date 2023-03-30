#pragma once

#include <linked_list.hpp>
#include <pivot_table_column.hpp>
#include <student.hpp>

class pivot_table {
private:
  list<label_type> label_types;
  list<pivot_table_column> columns;

public:
  pivot_table(const pivot_table &other);
  pivot_table(const list<label_type> &label_types);

  void append(const student &data);
  list<pivot_table_column> sorted();
};
