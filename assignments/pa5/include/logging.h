#pragma once

#include <ostream>
#include <utility>
#include <vector>

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

using LogEntry = std::pair<LogEntryKind, std::vector<int>>;

std::ostream &operator<<(std::ostream &os, const LogEntry &entry);
