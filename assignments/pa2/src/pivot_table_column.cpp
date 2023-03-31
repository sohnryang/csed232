#include <node.hpp>
#include <pivot_table_column.hpp>

int min(int x, int y) { return x < y ? x : y; }
int max(int x, int y) { return x > y ? x : y; }

pivot_table_column::pivot_table_column() : labels(), values() {}

pivot_table_column::pivot_table_column(const pivot_table_column &other)
    : labels(other.labels), values(other.values) {}

pivot_table_column::pivot_table_column(const list<std::string> &labels)
    : labels(labels), values() {}

int pivot_table_column::max_value() const {
  int result = values.head_node()->next->data;
  for_each(values, [&result](int v) { result = max(result, v); });
  return result;
}

int pivot_table_column::min_value() const {
  int result = values.head_node()->next->data;
  for_each(values, [&result](int v) { result = min(result, v); });
  return result;
}

float pivot_table_column::average_value() const {
  int sum = 0;
  for_each(values, [&sum](int v) { sum += v; });
  return (float)sum / values.size();
}

list<std::string> pivot_table_column::get_labels() const { return labels; }

void pivot_table_column::append(int value) { values.push_back(value); }
