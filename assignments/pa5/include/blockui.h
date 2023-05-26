#pragma once

#include "block.h"

#include <QLabel>
#include <QWidget>

#include <map>
#include <optional>

class BlockUi : public QLabel {
  Q_OBJECT

private:
  std::optional<Block> block_data = {};
  static const std::map<int, std::tuple<int, int, int>> color_table;

public:
  BlockUi(QWidget *parent = nullptr);
  BlockUi(const Block &block_data, QWidget *parent = nullptr);
};
