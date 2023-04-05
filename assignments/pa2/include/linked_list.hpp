#pragma once

#include <node.hpp>

#include <string>

// list is a doubly-linked list implementation.
template <typename T> class list {
private:
  // Count of nodes.
  int count;

  // Head and tail pointers.
  node<T> *head, *tail;

public:
  // Default constructor.
  list();

  // Copy constructor.
  list(const list<T> &other);

  // Destructor for deallocation.
  ~list();

  // Check if the list is empty.
  bool empty() const;

  // Calculate the size of the list.
  int size() const;

  // Getter for head node.
  node<T> *head_node() const;

  // Getter for tail node.
  node<T> *tail_node() const;

  // Append a data to the end of the list.
  void push_back(T data);

  // Search for a matching value
  node<T> *search(const T &data) const;

  // Search for a value x where predicate(x) == true.
  template <typename F> node<T> *search_pred(const F &predicate) const;
  void remove(node<T> *node_to_remove);

  // Check equality between lists. Only used for unit tests.
  bool operator==(const list<T> &other) const;
};

template <typename T> list<T>::list() : count(0) {
  // Create nodes for head and tail.
  head = new node<T>();
  tail = new node<T>();
  // At first, head and tail point each other.
  head->next = tail;
  tail->prev = head;
}

template <typename T> list<T>::list(const list<T> &other) : count(0) {
  // Do the same initialization as default constructor.
  head = new node<T>();
  tail = new node<T>();
  head->next = tail;
  tail->prev = head;

  // Copy nodes one by one.
  for_each(other, [this](const T &v) { push_back(v); });
}

template <typename T> list<T>::~list() {
  // Start from head node.
  node<T> *current = head;
  while (current) { // while current is not nullptr
    // We can't simply update current after deleting it since in would cause an
    // use-after-free error.
    node<T> *next_node = current->next;
    // Deallocate current node.
    delete current;
    // Continue to the next node.
    current = next_node;
  }
}

template <typename T> bool list<T>::empty() const {
  // Use count variable for empty checking.
  return count == 0;
}

template <typename T> int list<T>::size() const {
  // Return count variable.
  return count;
}

template <typename T> node<T> *list<T>::head_node() const {
  // Return head node.
  return head;
}

template <typename T> node<T> *list<T>::tail_node() const {
  // Return tail node.
  return tail;
}

template <typename T> void list<T>::push_back(T data) {
  // Create a new node to append to the list.
  node<T> *new_node = new node<T>(data);
  // The new node has to point to its previous node and tail.
  new_node->next = tail;
  new_node->prev = tail->prev;
  // Also, the existing nodes should point to the new node.
  tail->prev->next = new_node;
  tail->prev = new_node;
  // Increase node count.
  count++;
}

template <typename T> node<T> *list<T>::search(const T &data) const {
  // Use implemented search_pred
  return search_pred([&data](const T &v) { return v == data; });
}

template <typename T>
template <typename F>
node<T> *list<T>::search_pred(const F &predicate) const {
  // Start from the first node.
  node<T> *current = head->next;
  // Loop over the whole list.
  for (int i = 0; i < count; i++) {
    if (predicate(current->data)) // check if the predicate is true
      return current;             // return found node
    current = current->next;      // continue to the next node
  }
  return nullptr; // if nothing was found, return nullptr. (should have used
                  // std::optional)
}

template <typename T> void list<T>::remove(node<T> *node_to_remove) {
  // The existing nodes should not point to the node from removal.
  node_to_remove->prev->next = node_to_remove->next;
  node_to_remove->next->prev = node_to_remove->prev;
  // Deallocate node.
  delete node_to_remove;
  // Decrement the node count.
  count--;
}

template <typename T> bool list<T>::operator==(const list<T> &other) const {
  // If the counts are different, the lists are different.
  if (count != other.count)
    return false;
  node<T> *current = head->next, *other_current = other.head->next;
  for (int i = 0; i < count; i++) {
    if (current->data != other_current->data)
      return false;
    current = current->next;
    other_current = other_current->next;
  }
  return true;
}

template <typename T, typename F>
list<T> merge_lists(const list<T> &left, const list<T> &right,
                    const F &comparator) {
  // Create a list to store the merged result.
  list<T> merged;

  // Get the first nodes of both the input lists.
  node<T> *left_current = left.head_node()->next,
          *right_current = right.head_node()->next;

  // Iterate through both the input lists until we reach the end of one of them.
  while (left_current != left.tail_node() &&
         right_current != right.tail_node()) {
    // Compare the current data of both lists using the comparator function and
    // append the smaller one to the result.
    if (comparator(left_current->data, right_current->data) <= 0) {
      merged.push_back(left_current->data);
      left_current = left_current->next;
    } else {
      merged.push_back(right_current->data);
      right_current = right_current->next;
    }
  }

  // Append the remainder of the left list to the result.
  while (left_current != left.tail_node()) {
    merged.push_back(left_current->data);
    left_current = left_current->next;
  }

  // Append the remainder of the right list to the result.
  while (right_current != right.tail_node()) {
    merged.push_back(right_current->data);
    right_current = right_current->next;
  }
  return merged;
}

// sort with default ordering.
template <typename T> list<T> sort(const list<T> &list_to_sort) {
  return sort(list_to_sort, [](const T &v1, const T &v2) {
    if (v1 < v2)
      return -1;
    else if (v1 == v2)
      return 0;
    return 1;
  });
}

// sort with comparator function.
template <typename T, typename F>
list<T> sort(const list<T> &list_to_sort, const F &comparator) {
  if (list_to_sort.size() <= 1) // it is already sorted, so return it.
    return list_to_sort;

  // Divide the list into two halves.
  int left_size = list_to_sort.size() / 2;
  list<T> left, right;
  node<T> *current = list_to_sort.head_node()->next;
  for (int i = 0; i < left_size; i++) {
    left.push_back(current->data);
    current = current->next;
  }
  for (int i = left_size; i < list_to_sort.size(); i++) {
    right.push_back(current->data);
    current = current->next;
  }

  // Divide-and-conquer for two halves.
  list<T> left_sorted = sort(left, comparator),
          right_sorted = sort(right, comparator);
  // Merge the subarrays
  return merge_lists(left_sorted, right_sorted, comparator);
}

template <typename U, typename F, typename T>
list<U> map_function(const list<T> &list_to_map, const F &func) {
  // Create a list to store the mapped elements.
  list<U> result;

  // Traverse the original list.
  node<T> *current = list_to_map.head_node()->next;
  for (int i = 0; i < list_to_map.size(); i++) {
    result.push_back(func(current->data)); // apply the function

    // Continue to the next node
    current = current->next;
  }
  return result;
}

template <typename F, typename T>
void for_each(const list<T> &list_to_iterate, const F &func) {
  // Traverse the list.
  node<T> *current = list_to_iterate.head_node()->next;
  for (int i = 0; i < list_to_iterate.size(); i++) {
    // Apply the function to the current element.
    func(current->data);

    // Move to the next element in the list.
    current = current->next;
  }
}
