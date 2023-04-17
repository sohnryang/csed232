#include "classic.hpp"

#include <vector>

#include <gtest/gtest.h>

TEST(Artist, Classic) {
  int width = 2, height = 2;
  std::vector<int> sample_image = {width, height, 2, 18, 18, 37};
  classic c(width, height, sample_image);
  EXPECT_EQ(c.pixel_at(0, 0), 2);
  EXPECT_EQ(c.mapper(0, 0), '@');
  EXPECT_EQ(c.pixel_at(1, 0), 18);
  EXPECT_EQ(c.mapper(1, 0), '&');
  EXPECT_EQ(c.pixel_at(0, 1), 18);
  EXPECT_EQ(c.mapper(0, 1), '&');
  EXPECT_EQ(c.pixel_at(1, 1), 37);
  EXPECT_EQ(c.mapper(1, 1), '%');
}
