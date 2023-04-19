#include "parser.hpp"

#include <gtest/gtest.h>

#include <memory>
#include <sstream>
#include <string>
#include <vector>

TEST(Parser, PSVRead) {
  auto st = std::make_unique<std::stringstream>("abcd|efgh|ijkl|1234");
  parser p;
  EXPECT_EQ(p.read_psv(std::move(st)),
            std::vector<std::string>({"abcd", "efgh", "ijkl", "1234"}));
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
