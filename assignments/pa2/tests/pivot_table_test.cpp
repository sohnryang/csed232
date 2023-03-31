#include <pivot_table.hpp>

#include <gtest/gtest.h>

TEST(PivotTable, Append) {
  list<label_type> label_types;
  label_types.push_back(label_type::DEPT);
  label_types.push_back(label_type::GENDER);
  pivot_table pt(label_types);
  pt.append({"CS", "A", "M", 20});
  pt.append({"CS", "A1", "M", 20});
  pt.append({"CS", "B", "M", 20});
  pt.append({"MATH", "C", "M", 20});
  list<pivot_table_column> sorted_columns = pt.sorted();
  EXPECT_EQ(sorted_columns.size(), 2);
}
