#pragma once

#include <istream>
#include <memory>
#include <string>
#include <vector>

class parser {
public:
  // Read PSV (Pipe Separated Data) as vector of strings from provided
  // `input_stream`.
  std::vector<std::string> read_psv(std::unique_ptr<std::istream> input_stream);

  // Load image from path, `image_path`.
  std::vector<int> load_image(const char *image_path);

  // Load image from `input_stream`.
  std::vector<int> load_image(std::unique_ptr<std::istream> input_stream);

  // Load config from path, `config_path`.
  std::vector<std::string> load_config(const char *config_path);

  // Load config from `input_stream`.
  std::vector<std::string>
  load_config(std::unique_ptr<std::istream> input_stream);

  // Write ascii art in `ascii_art` to file in `output_path`.
  void write_result(const char *output_path, const std::string &ascii_art);
};
