#include <algorithm>
#include <iostream>
#include <string>

// to_string returns string representation of `num` in base `base`.
std::string to_string(int num, int base) {
  // We don't want to return empty string, so handle special case.
  if (num == 0)
    return "0";
  std::string res;
  while (num > 0) {
    int digit = num % base; // get the last digit using modulo operator
    char ch;                // converted digit
    if (digit <= 9) // handle ordinary case, where digit is within [0, 9]
      ch = (char)digit + '0';
    else // handle special case, where digit should be represented in alphabet
      ch = (char)digit - 10 + 'A';
    res = ch + res; // insert character to the beginning of the result
    num /= base;    // look at the next digit
  }
  return res;
}

int main() {
  int num, base;
  std::cin >> num >> base;                      // get input from user
  std::string converted = to_string(num, base); // convert the number to string
  std::cout << converted << std::endl;          // print converted string
  return 0;
}
