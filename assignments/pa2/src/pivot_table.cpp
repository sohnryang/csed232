#include <node.hpp>
#include <pivot_table.hpp>

pivot_table::pivot_table(const pivot_table &other)
    : label_types(other.label_types), columns(other.columns) {}

pivot_table::pivot_table(const list<label_type> &label_types)
    : label_types(label_types), columns() {}

void pivot_table::append(const student &data) {
  // Get the labels for the new data
  list<std::string> labels = map_function<std::string>(
      label_types, [&data](label_type t) { return data.get_label(t); });

  // Search for an existing column with the same labels
  node<pivot_table_column> *column_node =
      columns.search_pred([&labels](const pivot_table_column &v) {
        return v.get_labels() == labels;
      });

  // If no column with the same labels exists, create a new column and append
  // the data to it
  if (column_node == nullptr) {
    pivot_table_column new_column(labels);
    columns.push_back(new_column);
    append(data);
    return;
  }

  // If a column with the same labels exists, append the data to it
  column_node->data.append(data.get_value());
}

list<pivot_table_column> pivot_table::sorted() {
  return sort(
      columns,
      [](const pivot_table_column &c1, const pivot_table_column &c2) -> int {
        // Retrieve references to the labels of each column.
        const list<std::string> &c1_labels = c1.get_labels(),
                                &c2_labels = c2.get_labels();
        // Initialize node pointers to traverse the linked lists of labels.
        node<std::string> *c1_current = c1_labels.head_node()->next,
                          *c2_current = c2_labels.head_node()->next;
        // Compare each label at the same position in both columns.
        for (int i = 0; i < c1_labels.size(); i++) {
          // Compare the current labels and return the result if they differ.
          int compare_result = c1_current->data.compare(c2_current->data);
          if (compare_result != 0)
            return compare_result;
          // Advance the pointers to the next labels.
          c1_current = c1_current->next;
          c2_current = c2_current->next;
        }
        // All labels match, return 0 to indicate equality.
        return 0;
      });
}

list<label_type> pivot_table::get_label_types() const { return label_types; }
