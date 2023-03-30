#include <linked_list.hpp>

#include <string>

#include <gtest/gtest.h>

TEST(List, Init) {
  list<int> ls;
  EXPECT_TRUE(ls.empty());
  EXPECT_EQ(ls.size(), 0);
  EXPECT_EQ(ls.head_node()->next, ls.tail_node());
  EXPECT_EQ(ls.tail_node()->prev, ls.head_node());
}

TEST(List, Push) {
  list<int> ls;
  ls.push_back(0);
  ls.push_back(1);
  ls.push_back(2);
  EXPECT_EQ(ls.size(), 3);
  EXPECT_EQ(ls.head_node()->next->data, 0);
  EXPECT_EQ(ls.head_node()->next->next->data, 1);
  EXPECT_EQ(ls.head_node()->next->next->next->data, 2);
  EXPECT_EQ(ls.tail_node()->prev->data, 2);
  EXPECT_EQ(ls.tail_node()->prev->prev->data, 1);
  EXPECT_EQ(ls.tail_node()->prev->prev->prev->data, 0);
}

TEST(List, Search) {
  list<int> ls;
  ls.push_back(0);
  ls.push_back(1);
  ls.push_back(2);
  ls.push_back(3);
  ls.push_back(-1);
  EXPECT_EQ(ls.search(0), ls.head_node()->next);
  EXPECT_EQ(ls.search(1), ls.head_node()->next->next);
  EXPECT_EQ(ls.search(2), ls.head_node()->next->next->next);
  EXPECT_EQ(ls.search(3), ls.head_node()->next->next->next->next);
  EXPECT_EQ(ls.search(4), nullptr);
  EXPECT_EQ(ls.search_pred([](int v) { return v < 0; })->data, -1);

  list<std::string> strls;
  strls.push_back("hell");
  strls.push_back("world");
  strls.push_back("abcd");
  EXPECT_EQ(strls.search("hell")->data, "hell");
  EXPECT_EQ(
      strls.search_pred([](const auto &v) { return v.size() == 4; })->data,
      "hell");
}

TEST(List, Remove) {
  list<int> ls;
  ls.push_back(0);
  ls.push_back(42);
  ls.push_back(1024);
  node<int> *to_del = ls.search(42);
  ls.remove(to_del);
  EXPECT_EQ(ls.size(), 2);
  EXPECT_EQ(ls.head_node()->next->data, 0);
  to_del = ls.search(1024);
  ls.remove(to_del);
  EXPECT_EQ(ls.size(), 1);
  EXPECT_EQ(ls.head_node()->next->data, 0);
  to_del = ls.search(0);
  ls.remove(to_del);
  EXPECT_TRUE(ls.empty());
}

TEST(List, Sort) {
  list<int> ls;
  ls.push_back(4);
  ls.push_back(10);
  ls.push_back(0);
  ls.push_back(13);
  ls.push_back(-1);
  ls.push_back(1);
  list<int> sorted = sort(ls, [](int v1, int v2) { return v1 - v2; });
  EXPECT_EQ(sorted.head_node()->next->data, -1);
  EXPECT_EQ(sorted.head_node()->next->next->data, 0);
  EXPECT_EQ(sorted.head_node()->next->next->next->data, 1);
  EXPECT_EQ(sorted.head_node()->next->next->next->next->data, 4);
  EXPECT_EQ(sorted.head_node()->next->next->next->next->next->data, 10);
  EXPECT_EQ(sorted.head_node()->next->next->next->next->next->next->data, 13);
}

TEST(List, Equality) {
  list<int> ls;
  ls.push_back(1);
  ls.push_back(2);
  ls.push_back(0);
  list<int> ls2(ls);
  EXPECT_EQ(ls, ls2);
}
