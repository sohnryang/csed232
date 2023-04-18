#include "lexer.hpp"
#include "parser.hpp"

#include <gtest/gtest.h>

#include <memory>
#include <sstream>
#include <string>
#include <vector>

TEST(Lexer, UsualInput) {
  auto st = std::make_unique<std::stringstream>("42|abcd|1234| efgh|-128\n");
  lexer lex(std::move(st));
  EXPECT_EQ(lex.next_token(), token("42", token_kind::NUMBER));
  EXPECT_EQ(lex.next_token(), token("|", token_kind::SEPARATOR));
  EXPECT_EQ(lex.next_token(), token("abcd", token_kind::WORD));
  EXPECT_EQ(lex.next_token(), token("|", token_kind::SEPARATOR));
  EXPECT_EQ(lex.next_token(), token("1234", token_kind::NUMBER));
  EXPECT_EQ(lex.next_token(), token("|", token_kind::SEPARATOR));
  EXPECT_EQ(lex.next_token(), token("efgh", token_kind::WORD));
  EXPECT_EQ(lex.next_token(), token("|", token_kind::SEPARATOR));
  EXPECT_EQ(lex.next_token(), token("-128", token_kind::NUMBER));
  EXPECT_EQ(lex.next_token(), token("", token_kind::END));
}

TEST(Lexer, WhitespaceHandling) {
  auto st =
      std::make_unique<std::stringstream>(" |  42 |  abcd\n\t | efgh  \n");
  lexer lex(std::move(st));
  EXPECT_EQ(lex.next_token(), token("|", token_kind::SEPARATOR));
  EXPECT_EQ(lex.next_token(), token("42", token_kind::NUMBER));
  EXPECT_EQ(lex.next_token(), token("|", token_kind::SEPARATOR));
  EXPECT_EQ(lex.next_token(), token("abcd", token_kind::WORD));
  EXPECT_EQ(lex.next_token(), token("|", token_kind::SEPARATOR));
  EXPECT_EQ(lex.next_token(), token("efgh", token_kind::WORD));
  EXPECT_EQ(lex.next_token(), token("", token_kind::END));
}

TEST(Lexer, UnknownChar) {
  using namespace std::string_literals;
  auto st = std::make_unique<std::stringstream>("\0 42 | ^^v | abcdefg \n |"s);
  lexer lex(std::move(st));
  EXPECT_EQ(lex.next_token(), token("\0"s, token_kind::UNKNOWN));
  EXPECT_EQ(lex.next_token(), token("42", token_kind::NUMBER));
  EXPECT_EQ(lex.next_token(), token("|", token_kind::SEPARATOR));
  EXPECT_EQ(lex.next_token(), token("^", token_kind::UNKNOWN));
  EXPECT_EQ(lex.next_token(), token("^", token_kind::UNKNOWN));
  EXPECT_EQ(lex.next_token(), token("v", token_kind::WORD));
  EXPECT_EQ(lex.next_token(), token("|", token_kind::SEPARATOR));
  EXPECT_EQ(lex.next_token(), token("abcdefg", token_kind::WORD));
  EXPECT_EQ(lex.next_token(), token("|", token_kind::SEPARATOR));
  EXPECT_EQ(lex.next_token(), token("", token_kind::END));
}

TEST(Parser, LoadImage) {
  auto st = std::make_unique<std::stringstream>("3|2|101|102|103|104|105|106");
  parser p;
  std::vector<int> image_data = p.load_image(std::move(st));
  EXPECT_EQ(image_data, std::vector<int>({3, 2, 101, 102, 103, 104, 105, 106}));
}

TEST(Parser, LoadConfig) {
  auto st = std::make_unique<std::stringstream>("iclassic|upsample");
  parser p;
  std::vector<std::string> config_data = p.load_config(std::move(st));
  EXPECT_EQ(config_data, std::vector<std::string>({"iclassic", "upsample"}));
}
