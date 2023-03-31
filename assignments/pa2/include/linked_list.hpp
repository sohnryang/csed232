#pragma once

#include <node.hpp>

#include <string>

template <typename T> class list {
private:
  int count;
  node<T> *head, *tail;

public:
  list();
  list(const list<T> &other);
  ~list();

  bool empty() const;
  int size() const;
  node<T> *head_node() const;
  node<T> *tail_node() const;
  void push_back(T data);
  node<T> *search(const T &data) const;
  template <typename F> node<T> *search_pred(const F &predicate) const;
  void remove(node<T> *node_to_remove);

  bool operator==(const list<T> &other) const;
};

template <typename T> list<T>::list() : count(0) {
  head = new node<T>();
  tail = new node<T>();
  head->next = tail;
  tail->prev = head;
}

template <typename T> list<T>::list(const list<T> &other) : count(0) {
  head = new node<T>();
  tail = new node<T>();
  head->next = tail;
  tail->prev = head;
  node<T> *current = other.head->next;
  for (int i = 0; i < other.size(); i++) {
    push_back(current->data);
    current = current->next;
  }
}

template <typename T> list<T>::~list() {
  node<T> *current = head->next;
  while (current) {
    node<T> *next_node = current->next;
    delete current;
    current = next_node;
  }
}

template <typename T> bool list<T>::empty() const { return count == 0; }

template <typename T> int list<T>::size() const { return count; }

template <typename T> node<T> *list<T>::head_node() const { return head; }

template <typename T> node<T> *list<T>::tail_node() const { return tail; }

template <typename T> void list<T>::push_back(T data) {
  node<T> *new_node = new node<T>(data);
  new_node->next = tail;
  new_node->prev = tail->prev;
  tail->prev->next = new_node;
  tail->prev = new_node;
  count++;
}

template <typename T> node<T> *list<T>::search(const T &data) const {
  return search_pred([&data](const T &v) { return v == data; });
}

template <typename T>
template <typename F>
node<T> *list<T>::search_pred(const F &predicate) const {
  node<T> *current = head->next;
  for (int i = 0; i < count; i++) {
    if (predicate(current->data))
      return current;
    current = current->next;
  }
  return nullptr;
}

template <typename T> void list<T>::remove(node<T> *node_to_remove) {
  node_to_remove->prev->next = node_to_remove->next;
  node_to_remove->next->prev = node_to_remove->prev;
  delete node_to_remove;
  count--;
}

template <typename T> bool list<T>::operator==(const list<T> &other) const {
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
  list<T> merged;
  node<T> *left_current = left.head_node()->next,
          *right_current = right.head_node()->next;
  while (left_current != left.tail_node() &&
         right_current != right.tail_node()) {
    if (comparator(left_current->data, right_current->data) <= 0) {
      merged.push_back(left_current->data);
      left_current = left_current->next;
    } else {
      merged.push_back(right_current->data);
      right_current = right_current->next;
    }
  }
  while (left_current != left.tail_node()) {
    merged.push_back(left_current->data);
    left_current = left_current->next;
  }
  while (right_current != right.tail_node()) {
    merged.push_back(right_current->data);
    right_current = right_current->next;
  }
  return merged;
}

template <typename T, typename F>
list<T> sort(const list<T> &list_to_sort, const F &comparator) {
  if (list_to_sort.size() <= 1)
    return list_to_sort;
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
  list<T> left_sorted = sort(left, comparator),
          right_sorted = sort(right, comparator);
  return merge_lists(left_sorted, right_sorted, comparator);
}

template <typename U, typename F, typename T>
list<U> map_function(const list<T> &list_to_map, const F &func) {
  list<U> result;
  node<T> *current = list_to_map.head_node()->next;
  for (int i = 0; i < list_to_map.size(); i++) {
    result.push_back(func(current->data));
    current = current->next;
  }
  return result;
}

template <typename F, typename T>
void for_each(const list<T> &list_to_iterate, const F &func) {
  node<T> *current = list_to_iterate.head_node()->next;
  for (int i = 0; i < list_to_iterate.size(); i++) {
    func(current->data);
    current = current->next;
  }
}
