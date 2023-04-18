#pragma once

#include <istream>
#include <memory>
#include <string>
#include <utility>

enum class token_kind { NUMBER, WORD, SEPARATOR, END, UNKNOWN };
using token = std::pair<std::string, token_kind>;

class lexer {
private:
  int last_char;
  std::unique_ptr<std::istream> input_stream;

public:
  lexer(std::unique_ptr<std::istream> input_stream);
  token next_token();
};
