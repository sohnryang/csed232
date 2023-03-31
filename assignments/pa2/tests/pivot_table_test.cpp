#include <pivot_table.hpp>

#include <gtest/gtest.h>

TEST(PivotTable, AppendAndSort) {
  list<label_type> label_types;
  label_types.push_back(label_type::DEPT);
  label_types.push_back(label_type::GENDER);
  pivot_table pt(label_types);
  pt.append({"CS", "A", "M", 20});
  pt.append({"CS", "A1", "M", 21});
  pt.append({"CS", "B", "M", 20});
  pt.append({"MATH", "C", "M", 23});
  list<pivot_table_column> sorted_columns = pt.sorted();
  EXPECT_EQ(sorted_columns.size(), 2);
  list<std::string> labels_first, labels_second;
  labels_first.push_back("CS");
  labels_first.push_back("M");
  labels_second.push_back("MATH");
  labels_second.push_back("M");
  EXPECT_EQ(sorted_columns.head_node()->next->data.get_labels(), labels_first);
  EXPECT_EQ(sorted_columns.head_node()->next->data.min_value(), 20);
  EXPECT_EQ(sorted_columns.head_node()->next->data.max_value(), 21);
  EXPECT_EQ(sorted_columns.head_node()->next->next->data.get_labels(),
            labels_second);
  EXPECT_EQ(sorted_columns.head_node()->next->next->data.max_value(), 23);
}
