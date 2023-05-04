#include "SharedPtr.h"

class MyClass {
private:
  int m_id;
  static int n_objects;

public:
  explicit MyClass(int id = 0);
  ~MyClass();

  int get_id() const { return m_id; }

  static int num_objects() { return n_objects; }
};

int MyClass::n_objects = 0;

MyClass::MyClass(int id) : m_id(id) {
  n_objects++;
  std::cout << "MyClass object(" << m_id << ") created: " << n_objects
            << std::endl;
}

MyClass::~MyClass() {
  n_objects--;
  std::cout << "MyClass object(" << m_id << ") destroyed: " << n_objects
            << std::endl;
}

void test_SharedPtr() {
  std::cout << "test_SharedPtr()" << std::endl;

  SharedPtr<MyClass> ptr1(new MyClass(100));
  SharedPtr<MyClass> ptr2(ptr1);
  SharedPtr<MyClass> ptr3;
  ptr3 = ptr2;

  ptr1 = SharedPtr<MyClass>(new MyClass(200));

  std::cout << "=============" << std::endl;
  std::cout << "ptr1: " << ptr1->get_id() << std::endl;
  std::cout << "ptr2: " << (*ptr2).get_id() << std::endl;
  std::cout << "ptr3: " << ptr3->get_id() << std::endl;
  std::cout << "=============" << std::endl;

  ptr2 = ptr3 = ptr1;

  std::cout << "=============" << std::endl;
  std::cout << "ptr1: " << ptr1->get_id() << std::endl;
  std::cout << "ptr2: " << (*ptr2).get_id() << std::endl;
  std::cout << "ptr3: " << ptr3->get_id() << std::endl;
  std::cout << "=============" << std::endl;

  const SharedPtr<MyClass> const_ptr(new MyClass(300));
  std::cout << "=============" << std::endl;
  std::cout << "const_ptr: " << const_ptr->get_id() << std::endl;
  std::cout << "const_ptr: " << (*const_ptr).get_id() << std::endl;
  std::cout << "=============" << std::endl;

  const MyClass *pp = (const MyClass *)ptr1;
  std::cout << "pp: " << pp->get_id() << std::endl;
}

void test_SharedArray() {
  std::cout << "test_SharedArray()" << std::endl;

  SharedArray<int> arr1(new int[10]);
  SharedArray<int> arr2(arr1);
  SharedArray<int> arr3;
  arr3 = arr2;

  arr1[0] = 1;
  std::cout << "=============" << std::endl;
  std::cout << "arr1[0]: " << arr1[0] << std::endl;
  std::cout << "arr2[0]: " << arr2[0] << std::endl;
  std::cout << "arr3[0]: " << arr3[0] << std::endl;
  std::cout << "=============" << std::endl;

  arr1 = SharedArray<int>(new int[5]);
  arr1[0] = 2;
  arr2[0] = 3;

  std::cout << "=============" << std::endl;
  std::cout << "arr1[0]: " << arr1[0] << std::endl;
  std::cout << "arr2[0]: " << arr2[0] << std::endl;
  std::cout << "arr3[0]: " << arr3[0] << std::endl;
  std::cout << "=============" << std::endl;

  arr2 = arr3 = arr1;

  std::cout << "=============" << std::endl;
  std::cout << "arr1[0]: " << arr1[0] << std::endl;
  std::cout << "arr2[0]: " << arr2[0] << std::endl;
  std::cout << "arr3[0]: " << arr3[0] << std::endl;
  std::cout << "=============" << std::endl;
}

int main() {
  test_SharedPtr();
  std::cout << std::endl;
  test_SharedArray();
  return 0;
}
