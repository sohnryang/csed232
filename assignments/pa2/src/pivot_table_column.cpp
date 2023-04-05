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
  // Initialize the result to the first value in the list of values.
  int result = values.head_node()->next->data;
  // Iterate over the remaining values in the list, using a lambda function to
  // update the maximum.
  for_each(values, [&result](int v) { result = max(result, v); });
  // Return the maximum value.
  return result;
}

int pivot_table_column::min_value() const {
  // Initialize the result to the first value in the list of values.
  int result = values.head_node()->next->data;
  // Iterate over the remaining values in the list, using a lambda function to
  // update the minimum.
  for_each(values, [&result](int v) { result = min(result, v); });
  // Return the minimum value.
  return result;
}

float pivot_table_column::average_value() const {
  // Initialize a sum to zero.
  int sum = 0;
  // Iterate over the values in the list, using a lambda function to update the
  // sum.
  for_each(values, [&sum](int v) { sum += v; });
  // Calculate and return the average value by dividing the sum by the number of
  // values.
  return (float)sum / values.size();
}

list<std::string> pivot_table_column::get_labels() const { return labels; }

void pivot_table_column::append(int value) { values.push_back(value); }
