#include "parser.hpp"
#include "lexer.hpp"

#include <fstream>
#include <stdexcept>

std::vector<int> parser::load_image(const char *image_path) {
  auto input_stream = std::make_unique<std::ifstream>(image_path);
  return load_image(std::move(input_stream));
}

std::vector<int>
parser::load_image(std::unique_ptr<std::istream> input_stream) {
  lexer lex(std::move(input_stream));
  std::vector<int> res;
  int token_count = 0;
  token last_token("", token_kind::UNKNOWN);
  while (true) {
    last_token = lex.next_token();
    if (last_token.second == token_kind::END)
      break;
    if (token_count % 2 == 1 && last_token.second != token_kind::SEPARATOR)
      throw std::logic_error("expected SEPARATOR");
    else if (token_count % 2 == 0) {
      if (last_token.second != token_kind::NUMBER)
        throw std::logic_error("expected NUMBER");
      res.push_back(std::stoi(last_token.first));
    }
    token_count++;
  }
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
  lexer lex(std::move(input_stream));
  std::vector<std::string> res;
  int token_count = 0;
  token last_token("", token_kind::UNKNOWN);
  while (true) {
    last_token = lex.next_token();
    if (last_token.second == token_kind::END)
      break;
    if (token_count % 2 == 1 && last_token.second != token_kind::SEPARATOR)
      throw std::logic_error("expected SEPARATOR");
    else if (token_count % 2 == 0) {
      if (last_token.second != token_kind::WORD &&
          last_token.second != token_kind::NUMBER)
        throw std::logic_error("expected WORD");
      res.push_back(last_token.first);
    }
    token_count++;
  }
  return res;
}

void parser::write_result(const char *output_path,
                          const std::string &ascii_art) {
  std::ofstream fout(output_path);
  fout << ascii_art;
}
