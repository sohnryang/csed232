#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <cstdint>
#include <utility>

#include "Image.h"

using testing::Pair;

TEST(Image, Init) {
  Image<float> img(2, 2, 0.5f);
  EXPECT_EQ(img.width(), 2);
  EXPECT_EQ(img.height(), 2);
  for (int y = 0; y < 2; y++)
    for (int x = 0; x < 2; x++)
      EXPECT_EQ(img[y][x], 0.5f);
}

TEST(Image, Convert) {
  Image<RGB8b> img(4, 4);
  for (uint8_t y = 0; y < 4; y++)
    for (uint8_t x = 0; x < 4; x++)
      img[y][x] = {0, y, x};
  Image<float> avg = img.convert<float>(
      [](const RGB8b &p) { return (float)(p.r + p.g + p.b) / 3; });
  for (int y = 0; y < 4; y++)
    for (int x = 0; x < 4; x++)
      EXPECT_EQ(avg[y][x], (float)(y + x) / 3);
}

TEST(SliceRange, Init) {
  Image<nullptr_t>::SliceRange s1;
  EXPECT_EQ(s1.whole, true);

  Image<nullptr_t>::SliceRange s2(0, 42);
  EXPECT_EQ(s2.whole, false);
  EXPECT_EQ(s2.start, 0);
  EXPECT_EQ(s2.stop, 42);
  EXPECT_EQ(s2.step, 1);

  Image<nullptr_t>::SliceRange s3(0, 42, 2);
  EXPECT_EQ(s3.whole, false);
  EXPECT_EQ(s3.start, 0);
  EXPECT_EQ(s3.stop, 42);
  EXPECT_EQ(s3.step, 2);
}

TEST(SliceRange, Count) {
  Image<nullptr_t>::SliceRange s1;
  EXPECT_EQ(s1.count(), -1);

  Image<nullptr_t>::SliceRange s2(0, 42);
  EXPECT_EQ(s2.count(), 42);

  Image<nullptr_t>::SliceRange s3(0, 42, 10);
  EXPECT_EQ(s3.count(), 5);

  Image<nullptr_t>::SliceRange s4(42, 0);
  EXPECT_EQ(s4.count(), 0);

  Image<nullptr_t>::SliceRange s5(42, 0, -1);
  EXPECT_EQ(s5.count(), 42);

  Image<nullptr_t>::SliceRange s6(42, 0, -10);
  EXPECT_EQ(s6.count(), 5);
}

TEST(Image, Slice) {
  Image<std::pair<int, int>> img(10, 10);
  for (int y = 0; y < 10; y++)
    for (int x = 0; x < 10; x++)
      img[y][x] = {y, x};

  auto sliced1 = img.slice({0, 5}, {0, 10, 2});
  EXPECT_EQ(sliced1.width(), 5);
  EXPECT_EQ(sliced1.height(), 5);
  for (int y = 0; y < 5; y++)
    for (int x = 0; x < 5; x++)
      EXPECT_THAT(sliced1[y][x], Pair(y * 2, x));

  auto sliced2 = img.slice({}, {});
  EXPECT_EQ(sliced2.width(), img.width());
  EXPECT_EQ(sliced2.height(), img.height());
  for (int y = 0; y < 10; y++)
    for (int x = 0; x < 10; x++)
      EXPECT_EQ(sliced2[y][x], img[y][x]);

  auto sliced3 = img.slice({9, -1, -1}, {5, 10});
  EXPECT_EQ(sliced3.width(), 10);
  EXPECT_EQ(sliced3.height(), 5);
  for (int y = 0; y < 5; y++)
    for (int x = 0; x < 10; x++)
      EXPECT_THAT(sliced3[y][x], Pair(y + 5, 9 - x));
}
