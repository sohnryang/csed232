#pragma once

#include <string>

#include "student.hpp"

class node {
public:
  student data;
  node *next;
};

class list {
public:
  int count, dept_cnt;
  std::string dept[9];
  node *head;
  void sort(std::string metric);
};

void save_node(list &, node *);
void delete_node(list &, node *);
