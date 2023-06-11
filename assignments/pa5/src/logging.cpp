#include "src/logging.h"

#include <ostream>

std::ostream &operator<<(std::ostream &os, const LogEntry &entry) {
  switch (entry.first) {
  case LogEntryKind::INITIAL:
    os << "INITIAL";
    break;
  case LogEntryKind::UP:
    os << "UP";
    break;
  case LogEntryKind::DOWN:
    os << "DOWN";
    break;
  case LogEntryKind::LEFT:
    os << "LEFT";
    break;
  case LogEntryKind::RIGHT:
    os << "RIGHT";
    break;
  case LogEntryKind::GENERATE:
    os << "GENERATE";
    break;
  case LogEntryKind::MERGE:
    os << "MERGE";
    break;
  case LogEntryKind::RESTORE:
    os << "RESTORE";
    break;
  case LogEntryKind::SCORE:
    os << "SCORE";
    break;
  }
  for (const auto &v : entry.second)
    os << " " << v;
  return os;
}
