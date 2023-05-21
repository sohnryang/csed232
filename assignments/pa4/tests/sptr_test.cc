#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <string>
#include <utility>
#include <vector>

#include "SharedPtr.h"

using testing::Contains;
using testing::ElementsAre;

enum class LogKind { CREATED, DELETED };
using LogEntry = std::pair<LogKind, std::string>;
std::vector<LogEntry> global_alloc_log;

class DummyClass {
private:
  std::string name;
  static int object_count;
  std::vector<LogEntry> &logs;

public:
  explicit DummyClass(std::string name = "",
                      std::vector<LogEntry> &logs = global_alloc_log)
      : name(name), logs(logs) {
    object_count++;
    logs.push_back({LogKind::CREATED, name});
  }
  ~DummyClass() {
    object_count--;
    logs.push_back({LogKind::DELETED, name});
  }
  DummyClass &operator=(const DummyClass &that) {
    if (this == &that)
      return *this;
    name = that.name;
    logs = that.logs;
    return *this;
  }

  std::string get_name() const { return name; }
  static int get_count() { return object_count; }
};

int DummyClass::object_count = 0;

TEST(SharedPtr, Init) {
  std::vector<LogEntry> alloc_log;
  {
    SharedPtr<DummyClass> ptr(new DummyClass("Init", alloc_log));
    EXPECT_EQ(ptr->get_name(), "Init");
    EXPECT_EQ(DummyClass::get_count(), 1);
  }
  EXPECT_THAT(alloc_log, ElementsAre(LogEntry(LogKind::CREATED, "Init"),
                                     LogEntry(LogKind::DELETED, "Init")));
  EXPECT_EQ(DummyClass::get_count(), 0);
}

TEST(SharedPtr, CopyConstruct) {
  std::vector<LogEntry> alloc_log;
  {
    SharedPtr<DummyClass> ptr(new DummyClass("CopyConstruct", alloc_log));
    SharedPtr<DummyClass> ptr2(ptr);
    EXPECT_EQ(DummyClass::get_count(), 1);
    EXPECT_EQ(ptr2->get_name(), "CopyConstruct");
  }
  EXPECT_THAT(alloc_log,
              ElementsAre(LogEntry(LogKind::CREATED, "CopyConstruct"),
                          LogEntry(LogKind::DELETED, "CopyConstruct")));
}

TEST(SharedPtr, Assign) {
  std::vector<LogEntry> alloc_log;
  {
    SharedPtr<DummyClass> ptr(new DummyClass("Assign", alloc_log));
    SharedPtr<DummyClass> ptr2(new DummyClass("Assign2", alloc_log));
    EXPECT_EQ(DummyClass::get_count(), 2);
    ptr2 = ptr;
    EXPECT_EQ(DummyClass::get_count(), 1);
    EXPECT_EQ(ptr2->get_name(), "Assign");
    ptr = ptr2;
    EXPECT_EQ(DummyClass::get_count(), 1);
    EXPECT_EQ(ptr->get_name(), "Assign");
  }
  EXPECT_THAT(alloc_log, ElementsAre(LogEntry(LogKind::CREATED, "Assign"),
                                     LogEntry(LogKind::CREATED, "Assign2"),
                                     LogEntry(LogKind::DELETED, "Assign2"),
                                     LogEntry(LogKind::DELETED, "Assign")));

  alloc_log.clear();
  {
    SharedPtr<DummyClass> ptr(new DummyClass("Assign3", alloc_log));
    ptr = SharedPtr<DummyClass>(ptr);
  }
  EXPECT_THAT(alloc_log, ElementsAre(LogEntry(LogKind::CREATED, "Assign3"),
                                     LogEntry(LogKind::DELETED, "Assign3")));
}

TEST(SharedPtr, AssignChaining) {
  std::vector<LogEntry> alloc_log;
  {
    const SharedPtr<DummyClass> ptr(new DummyClass("Assign", alloc_log));
    SharedPtr<DummyClass> ptr2(new DummyClass("Assign2", alloc_log));
    SharedPtr<DummyClass> ptr3;
    EXPECT_EQ(DummyClass::get_count(), 2);
    ptr3 = ptr2 = ptr;
    EXPECT_EQ(DummyClass::get_count(), 1);
    EXPECT_EQ(ptr2->get_name(), "Assign");
    EXPECT_EQ(ptr3->get_name(), "Assign");
  }
  EXPECT_THAT(alloc_log, ElementsAre(LogEntry(LogKind::CREATED, "Assign"),
                                     LogEntry(LogKind::CREATED, "Assign2"),
                                     LogEntry(LogKind::DELETED, "Assign2"),
                                     LogEntry(LogKind::DELETED, "Assign")));
}

TEST(SharedArray, Init) {
  global_alloc_log.clear();
  {
    SharedArray<DummyClass> arr(new DummyClass[4]);
    for (int i = 0; i < 4; i++)
      arr[i] = DummyClass(std::to_string(i));
    for (int i = 0; i < 4; i++)
      EXPECT_EQ(arr[i].get_name(), std::to_string(i));
  }
  EXPECT_THAT(std::vector<LogEntry>(global_alloc_log.begin(),
                                    global_alloc_log.begin() + 4),
              Contains(LogEntry(LogKind::CREATED, "")).Times(4));
  for (int i = 0; i < 4; i++) {
    EXPECT_EQ(global_alloc_log[4 + 2 * i],
              LogEntry(LogKind::CREATED, std::to_string(i)));
    EXPECT_EQ(global_alloc_log[4 + 2 * i + 1],
              LogEntry(LogKind::DELETED, std::to_string(i)));
  }
  EXPECT_EQ(global_alloc_log.size(), 16);
}

TEST(SharedArray, Const) {
  global_alloc_log.clear();
  {
    const SharedArray<DummyClass> arr(new DummyClass[4]);
    for (int i = 0; i < 4; i++)
      EXPECT_EQ(arr[i].get_name(), "");
  }
  EXPECT_THAT(std::vector<LogEntry>(global_alloc_log.begin(),
                                    global_alloc_log.begin() + 4),
              Contains(LogEntry(LogKind::CREATED, "")).Times(4));
  EXPECT_THAT(std::vector<LogEntry>(global_alloc_log.begin() + 4,
                                    global_alloc_log.begin() + 8),
              Contains(LogEntry(LogKind::DELETED, "")).Times(4));
}
