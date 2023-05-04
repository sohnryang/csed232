#include "SharedPtr.h"

#include <cstddef>
#include <cstdint>

class TestClass {
private:
  int data;

public:
  TestClass(int data) : data(data) {}
  int get_data() const { return data; }
  void set_data(int x) { data = x; }
};

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  TestClass *c = new TestClass(42);
  SharedPtr<TestClass> ptr(c);
  for (int i = 0; i < Size; i++) {
    int cmd = Data[i] % 4;
    switch (cmd) {
    case 0: {
      SharedPtr<TestClass> tptr(nullptr);
      ptr = tptr;
      break;
    }
    case 1: {
      SharedPtr<TestClass> tptr;
      tptr = ptr;
      ptr = tptr;
      break;
    }
    case 2: {
      {
        SharedPtr<TestClass> tptr(new TestClass(128));
        ptr = tptr;
      }
      if (ptr->get_data() != 128)
        __builtin_trap();
      ptr->set_data(42);
      if (ptr->get_data() != 42)
        __builtin_trap();
      break;
    }
    case 3: {
      SharedPtr<TestClass> tptr(ptr);
      ptr = tptr;
      break;
    }
    }
  }
  return 0;
}
