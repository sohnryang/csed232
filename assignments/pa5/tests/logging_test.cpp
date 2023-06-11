#include "src/logging.h"

#include <gtest/gtest.h>

#include <sstream>

TEST(Logging, Output) {
  std::ostringstream st;
  LogEntry entries[] = {LogEntry(LogEntryKind::INITIAL, {1, 1, 3, 2}),
                        LogEntry(LogEntryKind::UP, {}),
                        LogEntry(LogEntryKind::DOWN, {}),
                        LogEntry(LogEntryKind::LEFT, {}),
                        LogEntry(LogEntryKind::RIGHT, {}),
                        LogEntry(LogEntryKind::GENERATE, {2, 1, 4}),
                        LogEntry(LogEntryKind::MERGE, {2, 2, 8}),
                        LogEntry(LogEntryKind::RESTORE, {1}),
                        LogEntry(LogEntryKind::SCORE, {72})};
  for (const auto entry : entries)
    st << entry << std::endl;
  EXPECT_EQ(st.str(), R"(INITIAL 1 1 3 2
UP
DOWN
LEFT
RIGHT
GENERATE 2 1 4
MERGE 2 2 8
RESTORE 1
SCORE 72
)");
}
