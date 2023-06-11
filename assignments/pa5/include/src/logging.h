#pragma once

#include <ostream>
#include <utility>
#include <vector>

// Enum for log entry types.
enum class LogEntryKind {
  INITIAL = 0,
  UP = 1,
  DOWN = 2,
  LEFT = 3,
  RIGHT = 4,
  GENERATE = 5,
  MERGE = 6,
  RESTORE = 7,
  SCORE = 8,
};

// Type alias for log entry.
using LogEntry = std::pair<LogEntryKind, std::vector<int>>;

// Operator overload for outputting to stream.
std::ostream &operator<<(std::ostream &os, const LogEntry &entry);
