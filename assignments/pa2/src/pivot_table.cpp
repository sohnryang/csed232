#include <node.hpp>
#include <pivot_table.hpp>

pivot_table::pivot_table(const pivot_table &other)
    : categories(other.categories), columns(other.columns) {}

pivot_table::pivot_table(const list<category> &categories)
    : categories(categories), columns() {}

void pivot_table::append(const student &data) {
  list<std::string> labels;
  node<category> *current = categories.head_node()->next;
  for (int i = 0; i < categories.size(); i++) {
    labels.push_back(data.get_label(current->data));
    current = current->next;
  }
  node<pivot_table_column> *column_node =
      columns.search_pred([&labels](const pivot_table_column &v) {
        return v.get_labels() == labels;
      });
  if (column_node == nullptr) {
    pivot_table_column new_column(labels);
    columns.push_back(new_column);
    append(data);
  }
  column_node->data.append(data.get_value());
}

list<pivot_table_column> pivot_table::sorted() {
  return sort(
      columns,
      [](const pivot_table_column &c1, const pivot_table_column &c2) -> int {
        const list<std::string> &c1_labels = c1.get_labels(),
                                &c2_labels = c2.get_labels();
        node<std::string> *c1_current = c1_labels.head_node()->next,
                          *c2_current = c2_labels.head_node()->next;
        for (int i = 0; i < c1_labels.size(); i++) {
          int compare_result = c1_current->data.compare(c2_current->data);
          if (compare_result != 0)
            return compare_result;
          c1_current = c1_current->next;
          c2_current = c2_current->next;
        }
        return 0;
      });
}
