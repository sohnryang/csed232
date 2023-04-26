#include "parser.hpp"

#include <algorithm>
#include <fstream>
#include <istream>
#include <iterator>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

std::vector<std::string>
parser::read_psv(std::unique_ptr<std::istream> input_stream) {
  std::vector<std::string> res;
  std::string whitespaces = " \t\v\n\r\f";
  while (!input_stream->eof()) {
    std::string token; // string variable to hold token
    // Read a line of input from input_stream and store it in token using '|' as
    // delimiter.
    std::getline(*input_stream, token, '|');

    // Trim whitespaces.
    token.erase(token.find_last_not_of(whitespaces) + 1);
    token.erase(0, token.find_first_not_of(whitespaces));

    res.push_back(token); // append token to res
  }
  return res; // return the vector of strings
}

std::vector<int> parser::load_image(const char *image_path) {
  // Create a unique_ptr to ifstream object with the given image_path.
  auto input_stream = std::make_unique<std::ifstream>(image_path);

  // Call `load_image` with the unique_ptr to ifstream object.
  return load_image(std::move(input_stream));
}

std::vector<int>
parser::load_image(std::unique_ptr<std::istream> input_stream) {
  // Read '|' separated values from input_stream and store it in `psv`.
  std::vector<std::string> psv = read_psv(std::move(input_stream));
  std::vector<int> res; // create a vector of integers

  // Transform each string element of `psv` to int and store it in `res`.
  std::transform(psv.cbegin(), psv.cend(), std::back_inserter(res),
                 [](const std::string &s) { return std::stoi(s); });

  // Check the size of `res`.
  if (res.size() < 2 || res.size() != res[0] * res[1] + 2)
    throw std::logic_error("invalid image size"); // throw an exception
  return res; // return the vector of integers
}

std::vector<std::string> parser::load_config(const char *config_path) {
  // Create a unique_ptr to ifstream object with the given `config_path`.
  auto input_stream = std::make_unique<std::ifstream>(config_path);

  // Call load_config with the unique_ptr to ifstream object.
  return load_config(std::move(input_stream));
}

std::vector<std::string>
parser::load_config(std::unique_ptr<std::istream> input_stream) {
  // Read '|' separated values from `input_stream` and return it
  return read_psv(std::move(input_stream));
}

void parser::write_result(const char *output_path,
                          const std::string &ascii_art) {
  // Create an ofstream object with the given `output_path`.
  std::ofstream fout(output_path);
  fout << ascii_art; // write ascii_art to fout
}
