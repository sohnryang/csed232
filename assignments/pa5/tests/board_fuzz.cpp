#include "src/board.h"

#include <cstddef>
#include <cstdint>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  Board b;
  for (int i = 0; i < Size; i++) {
    if (b.is_finished())
      b = Board();
    auto insert_cands = b.vacant_pos();
    if (insert_cands.empty()) {
      auto insert_pos = insert_cands[Data[i] % insert_cands.size()];
      b[insert_pos] = 1;
    }
    b.move_board(static_cast<InputKind>(Data[i] % 4));
  }
  return 0;
}
