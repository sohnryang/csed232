#include "block.h"
#include "board.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <array>
#include <utility>
#include <vector>

using testing::ElementsAre;
using testing::Eq;
using testing::IsEmpty;

TEST(Board, Init) {
  Board b;
  for (int y = 0; y < 4; y++)
    for (int x = 0; x < 4; x++) {
      auto block = b[{y, x}];
      EXPECT_FALSE(block.has_value());
    }
}

TEST(Board, Index) {
  Board b({std::array<BoardEntry, 4>{1, 2, 3, 4},
           {5, 6, 7, 8},
           {9, 10, 11, 12},
           {13, 14, 15, 16}});
  for (int y = 0; y < 4; y++)
    for (int x = 0; x < 4; x++) {
      auto block = b[{y, x}];
      EXPECT_EQ(block, y * 4 + x + 1);
    }
  b[{0, 0}] = {};
  auto block = b[{0, 0}];
  EXPECT_FALSE(block.has_value());
  b[{1, 0}] = 3;
  block = b[{1, 0}];
  EXPECT_EQ(block, 3);
}

TEST(Board, RowAt) {
  Board b({std::array<BoardEntry, 4>{1, 2, 3, 4},
           {5, 6, 7, 8},
           {9, 10, 11, 12},
           {13, 14, 15, 16}});
  EXPECT_THAT(b.row_at(0), ElementsAre(Eq(1), Eq(2), Eq(3), Eq(4)));
  EXPECT_THAT(b.row_at(1), ElementsAre(Eq(5), Eq(6), Eq(7), Eq(8)));
}

TEST(Board, ColAt) {
  Board b({std::array<BoardEntry, 4>{1, 2, 3, 4},
           {5, 6, 7, 8},
           {9, 10, 11, 12},
           {13, 14, 15, 16}});
  EXPECT_THAT(b.column_at(0), ElementsAre(Eq(1), Eq(5), Eq(9), Eq(13)));
  EXPECT_THAT(b.column_at(1), ElementsAre(Eq(2), Eq(6), Eq(10), Eq(14)));
}

TEST(Board, Compactify) {
  {
    std::vector<BoardEntry> line = {{}, 1, 1, {}};
    auto [compactified, score] = Board::reduce_line(line);
    EXPECT_THAT(compactified, ElementsAre(Eq(2)));
    EXPECT_EQ(score, 4);
  }
  {
    std::vector<BoardEntry> line = {{}, {}};
    auto [compactified, score] = Board::reduce_line(line);
    EXPECT_THAT(compactified, IsEmpty());
    EXPECT_EQ(score, 0);
  }
  {
    std::vector<BoardEntry> line = {1, 1, 2, 2};
    auto [compactified, score] = Board::reduce_line(line);
    EXPECT_THAT(compactified, ElementsAre(Eq(2), Eq(3)));
    EXPECT_EQ(score, 12);
  }
  {
    std::vector<BoardEntry> line = {1, 2, 2, {}};
    auto [compactified, score] = Board::reduce_line(line);
    EXPECT_THAT(compactified, ElementsAre(Eq(1), Eq(3)));
    EXPECT_EQ(score, 8);
  }
}

TEST(Board, CheckMovable) {
  {
    Board b;
    EXPECT_FALSE(b.check_movable());
  }
  {
    Board b({std::array<BoardEntry, 4>{1, 2, 3, 4},
             {5, 6, 7, 8},
             {9, 10, 11, 12},
             {13, 14, 15, 16}});
    EXPECT_FALSE(b.check_movable());
  }
  {
    Board b({std::array<BoardEntry, 4>{1, {}, {}, {}},
             {1, {}, {}, {}},
             {1, {}, {}, {}},
             {1, {}, {}, {}}});
    EXPECT_TRUE(b.check_movable());
  }
}

TEST(Board, IsFinished) {
  {
    Board b;
    EXPECT_FALSE(b.is_finished());
  }
  {
    Board b({std::array<BoardEntry, 4>{1, 2, 3, 4},
             {5, 6, 7, 8},
             {9, 10, 11, 12},
             {13, 14, 15, 16}});
    EXPECT_TRUE(b.is_finished());
  }
  {
    Board b({std::array<BoardEntry, 4>{1, {}, {}, {}},
             {1, {}, {}, {}},
             {1, {}, {}, {}},
             {1, {}, {}, {}}});
    EXPECT_FALSE(b.is_finished());
  }
}

TEST(Board, MoveBoard) {
  {
    Board b;
    BoardMatrix bm = b.get_board_matrix();
    EXPECT_EQ(b.move_board(InputKind::UP), 0);
    EXPECT_EQ(b.get_board_matrix(), bm);
  }
  {
    Board b({std::array<BoardEntry, 4>{1, 2, 3, 4},
             {5, 6, 7, 8},
             {9, 10, 11, 12},
             {13, 14, 15, 16}});
    EXPECT_EQ(b.move_board(InputKind::UP), 0);
    EXPECT_EQ(b.move_board(InputKind::DOWN), 0);
    EXPECT_EQ(b.move_board(InputKind::LEFT), 0);
    EXPECT_EQ(b.move_board(InputKind::RIGHT), 0);
  }
}
