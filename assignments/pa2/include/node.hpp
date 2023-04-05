#pragma once

// node is one node of linked list.
template <typename T> class node {
public:
  // Data held by node
  T data;

  // Pointer to the previous and next node
  node<T> *prev, *next;

  // Default constructor.
  node();

  // Constructor with data.
  node(T data);
};

template <typename T> node<T>::node() : data(), prev(nullptr), next(nullptr) {}

template <typename T>
node<T>::node(T data) : data(data), prev(nullptr), next(nullptr) {}
