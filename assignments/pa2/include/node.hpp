#pragma once

template <typename T> class node {
public:
  T data;
  node<T> *prev, *next;
  node();
  node(T data);
};

template <typename T> node<T>::node() : data(), prev(nullptr), next(nullptr) {}

template <typename T>
node<T>::node(T data) : data(data), prev(nullptr), next(nullptr) {}
