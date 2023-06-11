#pragma once

#include "src/block.h"

#include <QLabel>
#include <QWidget>

#include <map>
#include <optional>

class BlockUi : public QLabel {
  Q_OBJECT

private:
  // Data of the block which is being shown.
  std::optional<Block> block_data = {};

  // Color table for setting colors.
  static const std::map<int, std::tuple<int, int, int>> color_table;

public:
  // Constructor with given parent.
  BlockUi(QWidget *parent = nullptr);

  // Constructor with block given.
  BlockUi(QWidget *parent, const Block &block_data);
};
