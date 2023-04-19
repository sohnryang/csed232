#pragma once

#include <istream>
#include <memory>
#include <string>
#include <vector>

class parser {
public:
  std::vector<int> load_image(const char *image_path);
  std::vector<int> load_image(std::unique_ptr<std::istream> input_stream);
  std::vector<std::string> load_config(const char *config_path);
  std::vector<std::string>
  load_config(std::unique_ptr<std::istream> input_stream);
  void write_result(const char *output_path, const std::string &ascii_art);
};
