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
  Board b(
      {BoardRow{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}});
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
  Board b(
      {BoardRow{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}});
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

TEST(Board, VacantPos) {
  Board b(
      {BoardRow{1, 2, 3, 4}, {6, {}, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}});
  EXPECT_THAT(b.vacant_pos(), ElementsAre(Eq(std::make_pair(1, 1))));
}

TEST(Board, Compactify) {
  {
    std::vector<BoardEntry> line = {{}, 1, 1, {}};
    auto [compactified, created_blocks] = Board::reduce_line(line);
    EXPECT_THAT(compactified, ElementsAre(Eq(2)));
    std::vector<std::pair<Block, int>> expected = {{2, 0}};
    EXPECT_EQ(created_blocks, expected);
  }
  {
    std::vector<BoardEntry> line = {{}, {}};
    auto [compactified, created_blocks] = Board::reduce_line(line);
    EXPECT_THAT(compactified, IsEmpty());
    EXPECT_THAT(created_blocks, IsEmpty());
  }
  {
    std::vector<BoardEntry> line = {1, 1, 2, 2};
    auto [compactified, created_blocks] = Board::reduce_line(line);
    EXPECT_THAT(compactified, ElementsAre(Eq(2), Eq(3)));
    std::vector<std::pair<Block, int>> expected = {{2, 0}, {3, 1}};
    EXPECT_EQ(created_blocks, expected);
  }
  {
    std::vector<BoardEntry> line = {1, 2, 2, {}};
    auto [compactified, created_blocks] = Board::reduce_line(line);
    EXPECT_THAT(compactified, ElementsAre(Eq(1), Eq(3)));
    std::vector<std::pair<Block, int>> expected = {{3, 1}};
    EXPECT_EQ(created_blocks, expected);
  }
}

TEST(Board, CheckMovable) {
  {
    Board b;
    EXPECT_FALSE(b.check_movable());
  }
  {
    Board b({BoardRow{1, 2, 3, 4},
             {5, 6, 7, 8},
             {9, 10, 11, 12},
             {13, 14, 15, 16}});
    EXPECT_FALSE(b.check_movable());
  }
  {
    Board b({BoardRow{1, {}, {}, {}},
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
    Board b({BoardRow{1, 2, 3, 4},
             {5, 6, 7, 8},
             {9, 10, 11, 12},
             {13, 14, 15, 16}});
    EXPECT_TRUE(b.is_finished());
  }
  {
    Board b({BoardRow{1, {}, {}, {}},
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
    EXPECT_THAT(b.move_board(InputKind::UP), IsEmpty());
    EXPECT_EQ(b.get_board_matrix(), bm);
  }
  {
    Board b({BoardRow{1, 2, 3, 4},
             {5, 6, 7, 8},
             {9, 10, 11, 12},
             {13, 14, 15, 16}});
    EXPECT_THAT(b.move_board(InputKind::UP), IsEmpty());
    EXPECT_THAT(b.move_board(InputKind::DOWN), IsEmpty());
    EXPECT_THAT(b.move_board(InputKind::LEFT), IsEmpty());
    EXPECT_THAT(b.move_board(InputKind::RIGHT), IsEmpty());
  }
  {
    /*
     * 02 XX 02 XX
     * 02 XX XX XX
     * 02 XX 02 04
     * 02 XX XX 04
     */
    Board b({BoardRow{1, {}, 1}, {1}, {1, {}, 1, 2}, {1, {}, {}, 2}});

    /*
     * 04 XX 04 08
     * 04 XX XX XX
     * XX XX XX XX
     * XX XX XX XX
     */
    std::vector<std::pair<Block, std::pair<int, int>>> expected_created = {
        {2, {0, 0}}, {2, {0, 2}}, {3, {0, 3}}, {2, {1, 0}}};
    EXPECT_EQ(b.move_board(InputKind::UP), expected_created);
    BoardMatrix expected_matrix = {BoardRow{2, {}, 2, 3}, BoardRow{2}};
    EXPECT_EQ(b.get_board_matrix(), expected_matrix);

    /*
     * 08 08 XX XX
     * 04 XX XX XX
     * XX XX XX XX
     * XX XX XX XX
     */
    std::vector<std::pair<Block, std::pair<int, int>>> expected_created2 = {
        {3, {0, 0}}};
    EXPECT_EQ(b.move_board(InputKind::LEFT), expected_created2);
    BoardMatrix expected_matrix2 = {BoardRow{3, 3}, BoardRow{2}};
    EXPECT_EQ(b.get_board_matrix(), expected_matrix2);

    /*
     * XX XX XX 16
     * XX XX XX 04
     * XX XX XX XX
     * XX XX XX XX
     */
    std::vector<std::pair<Block, std::pair<int, int>>> expected_created3 = {
        {4, {0, 3}}};
    EXPECT_EQ(b.move_board(InputKind::RIGHT), expected_created3);
    BoardMatrix expected_matrix3;
    expected_matrix3[0][3] = 4;
    expected_matrix3[1][3] = 2;
    EXPECT_EQ(b.get_board_matrix(), expected_matrix3);
  }
  {
    /*
     * XX XX 02 XX
     * XX XX XX XX
     * 02 XX 02 04
     * 02 XX XX 04
     */
    Board b;
    b[{0, 2}] = 1;
    b[{2, 0}] = 1;
    b[{2, 2}] = 1;
    b[{2, 3}] = 2;
    b[{3, 0}] = 1;
    b[{3, 3}] = 2;

    /*
     * XX XX XX XX
     * XX XX XX XX
     * XX XX XX XX
     * 04 XX 04 08
     */
    std::vector<std::pair<Block, std::pair<int, int>>> expected_created = {
        {2, {3, 0}}, {2, {3, 2}}, {3, {3, 3}}};
    EXPECT_EQ(b.move_board(InputKind::DOWN), expected_created);
    BoardMatrix expected_matrix;
    expected_matrix[3] = {2, {}, 2, 3};
    EXPECT_EQ(b.get_board_matrix(), expected_matrix);
  }
}
