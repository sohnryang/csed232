#include <node.hpp>
#include <pivot_table_column.hpp>

int min(int x, int y) { return x < y ? x : y; }
int max(int x, int y) { return x > y ? x : y; }

pivot_table_column::pivot_table_column(const pivot_table_column &other)
    : labels(other.labels), values(other.values) {}

pivot_table_column::pivot_table_column(const list<std::string> &labels)
    : labels(labels), values() {}

int pivot_table_column::max_value() const {
  node<int> *current = values.head_node()->next;
  int result = current->data;
  for (int i = 0; i < values.size(); i++) {
    result = max(result, current->data);
    current = current->next;
  }
  return result;
}

int pivot_table_column::min_value() const {
  node<int> *current = values.head_node()->next;
  int result = current->data;
  for (int i = 0; i < values.size(); i++) {
    result = min(result, current->data);
    current = current->next;
  }
  return result;
}

float pivot_table_column::average_value() const {
  node<int> *current = values.head_node()->next;
  int sum = 0;
  for (int i = 0; i < values.size(); i++) {
    sum += current->data;
    current = current->next;
  }
  return (float)sum / values.size();
}

void pivot_table_column::append(int value) { values.push_back(value); }
