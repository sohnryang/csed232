#include <linked_list.hpp>

#include <cstddef>
#include <cstdint>

int fuzz(const uint8_t *data, size_t size) {
  list<int> ls;
  int ls_size = 0;
  for (int i = 1; i < size; i += 2) {
    int cmd = data[i - 1] % 4, arg = data[i];
    switch (cmd) {
    case 0:
      ls.push_back(arg);
      ls_size++;
      break;
    case 1: {
      auto n = ls.search(arg);
      if (n == nullptr)
        break;
      ls.remove(n);
      ls_size--;
      break;
    }
    case 2: {
      if (ls.empty())
        break;
      list<int> sorted = sort(ls, [](int v1, int v2) { return v1 - v2; });
      int last = sorted.head_node()->next->data;
      bool is_sorted = true;
      for_each(sorted, [&last, &is_sorted](int v) {
        is_sorted = is_sorted && last <= v;
        last = v;
      });
      if (!is_sorted)
        return 1;
      break;
    }
    default:
      if (ls_size != ls.size())
        return 1;
    }
  }
  return 0;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  if (fuzz(Data, Size))
    __builtin_trap();
  return 0;
}
