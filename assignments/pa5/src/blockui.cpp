#include "blockui.h"
#include "block.h"

#include <Qt>

#include <optional>
#include <sstream>
#include <string>
#include <tuple>

const std::map<int, std::tuple<int, int, int>> BlockUi::color_table = {
    {1, {187, 173, 160}}, {2, {237, 224, 200}}, {3, {242, 177, 121}},
    {4, {245, 149, 99}},  {5, {246, 126, 95}},  {6, {246, 94, 59}},
    {7, {237, 207, 114}}, {8, {237, 204, 97}},  {9, {237, 200, 80}},
    {10, {237, 197, 63}}, {11, {237, 194, 46}}};

BlockUi::BlockUi(QWidget *parent) : QLabel("", parent) {
  resize(250, 250);
  setStyleSheet("QLabel { background: rgb(255, 255, 255); color: black; "
                "border-style: solid; font: 70pt; font: bold; }");
}

BlockUi::BlockUi(const Block &block_data, QWidget *parent)
    : block_data(block_data),
      QLabel(std::to_string(1 << block_data.get_power()).c_str(), parent) {
  resize(250, 250);
  auto [r, g, b] = color_table.at(block_data.get_power());
  std::stringstream st;
  st << "QLabel { background: rgb(" << r << ", " << g << ", " << b
     << "); color: black; border-style: solid; font: 70pt; font: bold; }";
  setStyleSheet(st.str().c_str());
  setAlignment(Qt::AlignCenter);
}
