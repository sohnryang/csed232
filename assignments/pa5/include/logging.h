#pragma once

#include <ostream>
#include <utility>
#include <vector>

enum class LogEntryKind {
  INITIAL,
  UP,
  DOWN,
  LEFT,
  RIGHT,
  GENERATE,
  MERGE,
  RESTORE,
  SCORE,
};

using LogEntry = std::pair<LogEntryKind, std::vector<int>>;

std::ostream &operator<<(std::ostream &os, const LogEntry &entry);
