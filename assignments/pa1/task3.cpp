#include <cstring>
#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

// parse_int parses int in std::string.
int parse_int(const string &str) {
  int base = 10;             // base 10 integer by default
  string number_part = str;  // string with stripped prefix
  if (str.find("0X") == 0) { // if the prefix indicates base 16
    base = 16;
    number_part = str.substr(2);    // strip prefix
  } else if (str.find("0b") == 0) { // if the prefix indicates base 2
    base = 2;
    number_part = str.substr(2);   // strip prefix
  } else if (str.find("0") == 0) { // if the prefix indicates base 8
    base = 8;
    number_part = str.substr(1); // strip prefix
  }
  int res = 0;
  for (auto &ch : number_part) {
    res *= base; // shift by one digit
    int digit;
    if (ch >= 'A') // check if current digit in string is alphabet
      digit = ch - 'A' + 10;
    else // check if current digit in string is numeric
      digit = ch - '0';
    res += digit; // add digit to result
  }
  return res;
}

int main() {
  char op[7]; // C style string for operator
  string operand1_str, operand2_str;
  int result;
  cin >> op >> operand1_str;                 // get operator and first operand
  int operand1 = parse_int(operand1_str); // parse string form of operand 1
  if (strcmp(op, "square") == 0)          // check unary operator
    result = operand1 * operand1;         // calculate square
  else if (strcmp(op, "sqrt") == 0)
    result = sqrt(operand1); // calculate sqrt
  else {                     // case for binary operator
    cin >> operand2_str;     // get second operand
    int operand2 = parse_int(operand2_str); // parse string form of operator 2
    if (strcmp(op, "+") == 0)
      result = operand1 + operand2; // calculate addition
    else if (strcmp(op, "-") == 0)
      result = operand1 - operand2; // calculate substraction
    else if (strcmp(op, "*") == 0)
      result = operand1 * operand2; // calculate multiplication
    else if (strcmp(op, "/") == 0)
      result = operand1 / operand2; // calculate division
  }
  std::cout << result << std::endl;
  return 0;
}
