#include "classic.hpp"
#include "iclassic.hpp"
#include "sobelx.hpp"

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

TEST(Artist, Iclassic) {
  int width = 2, height = 2;
  std::vector<int> sample_image = {width, height, 2, 18, 18, 37};
  iclassic ic(width, height, sample_image);
  EXPECT_EQ(ic.pixel_at(0, 0), 2);
  EXPECT_EQ(ic.mapper(0, 0), ' ');
  EXPECT_EQ(ic.pixel_at(1, 0), 18);
  EXPECT_EQ(ic.mapper(1, 0), '.');
  EXPECT_EQ(ic.pixel_at(0, 1), 18);
  EXPECT_EQ(ic.mapper(0, 1), '.');
  EXPECT_EQ(ic.pixel_at(1, 1), 37);
  EXPECT_EQ(ic.mapper(1, 1), '-');
}

TEST(Artist, SobelX) {
  int width = 3, height = 3;
  std::vector<int> sample_image = {width, height, 100, 160, 120, 100,
                                   30,    100,    100, 100, 170};
  sobelx sx(width, height, sample_image);
  EXPECT_EQ(sx.mapper(0, 0), '|');
  EXPECT_EQ(sx.mapper(1, 0), ' ');
  EXPECT_EQ(sx.mapper(2, 0), ' ');
  EXPECT_EQ(sx.mapper(0, 1), '|');
  EXPECT_EQ(sx.mapper(1, 1), '|');
  EXPECT_EQ(sx.mapper(2, 1), ' ');
  EXPECT_EQ(sx.mapper(0, 2), ' ');
  EXPECT_EQ(sx.mapper(1, 2), '|');
  EXPECT_EQ(sx.mapper(2, 2), ' ');
}
