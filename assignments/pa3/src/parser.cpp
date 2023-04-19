#include "parser.hpp"

#include <algorithm>
#include <fstream>
#include <iterator>
#include <stdexcept>

std::vector<std::string>
parser::read_psv(std::unique_ptr<std::istream> input_stream) {
  std::vector<std::string> res;
  while (!input_stream->eof()) {
    std::string token;
    std::getline(*input_stream, token, '|');
    res.push_back(token);
  }
  return res;
}

std::vector<int> parser::load_image(const char *image_path) {
  auto input_stream = std::make_unique<std::ifstream>(image_path);
  return load_image(std::move(input_stream));
}

std::vector<int>
parser::load_image(std::unique_ptr<std::istream> input_stream) {
  std::vector<std::string> psv = read_psv(std::move(input_stream));
  std::vector<int> res;
  std::transform(psv.cbegin(), psv.cend(), std::back_inserter(res),
                 [](const std::string &s) { return std::stoi(s); });
  if (res.size() < 2 || res.size() != res[0] * res[1] + 2)
    throw std::logic_error("invalid image size");
  return res;
}

std::vector<std::string> parser::load_config(const char *config_path) {
  auto input_stream = std::make_unique<std::ifstream>(config_path);
  return load_config(std::move(input_stream));
}

std::vector<std::string>
parser::load_config(std::unique_ptr<std::istream> input_stream) {
  return read_psv(std::move(input_stream));
}

void parser::write_result(const char *output_path,
                          const std::string &ascii_art) {
  std::ofstream fout(output_path);
  fout << ascii_art;
}
