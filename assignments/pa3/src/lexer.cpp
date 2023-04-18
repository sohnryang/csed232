#include "lexer.hpp"

#include <cctype>

lexer::lexer(std::unique_ptr<std::istream> input_stream)
    : input_stream(std::move(input_stream)), last_char(' ') {}

token lexer::next_token() {
  while (std::isspace(last_char))
    last_char = input_stream->get();
  if (input_stream->eof())
    return {"", token_kind::END};
  if (last_char == '|') {
    last_char = input_stream->get();
    return {"|", token_kind::SEPARATOR};
  }
  if (std::isdigit(last_char) || last_char == '-' || last_char == '+') {
    std::string num_str;
    do {
      num_str += last_char;
      last_char = input_stream->get();
    } while (std::isdigit(last_char));
    return {num_str, token_kind::NUMBER};
  }
  if (std::isalpha(last_char)) {
    std::string word;
    do {
      word += last_char;
      last_char = input_stream->get();
    } while (std::isalpha(last_char));
    return {word, token_kind::WORD};
  }
  auto res = token(std::string({char(last_char)}), token_kind::UNKNOWN);
  last_char = input_stream->get();
  return res;
}
