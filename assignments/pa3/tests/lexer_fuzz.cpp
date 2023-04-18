#include "lexer.hpp"

#include <cstddef>
#include <cstdint>
#include <memory>
#include <sstream>
#include <string>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  auto st =
      std::make_unique<std::stringstream>(std::string((char *)Data, Size));
  lexer lex(std::move(st));
  token current_token = lex.next_token();
  while (current_token.second != token_kind::END) {
    if (current_token.second == token_kind::UNKNOWN)
      return -1;
    current_token = lex.next_token();
  }
  return 0;
}
