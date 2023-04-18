#include "drawer.hpp"
#include "gradient.hpp"

#include <vector>

#include <gtest/gtest.h>

TEST(Drawer, Drawer) {
  int width = 3, height = 3;
  std::vector<int> sample_image = {width, height, 100, 160, 120, 100,
                                   30,    100,    100, 100, 170};
  gradient g(width, height, sample_image);
  drawer d(&g);
  EXPECT_EQ(d.draw(), R"(|- 
|+-
 | 
)");
}
