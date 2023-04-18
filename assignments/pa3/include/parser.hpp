#pragma once

#include <istream>
#include <memory>
#include <string>
#include <vector>

class parser {
public:
  std::vector<int> load_image(const char *);
  std::vector<int> load_image(std::unique_ptr<std::istream>);
  std::vector<std::string> load_config(const char *);
  std::vector<std::string> load_config(std::unique_ptr<std::istream>);
  void write_result(const char *, const std::string &);
};
