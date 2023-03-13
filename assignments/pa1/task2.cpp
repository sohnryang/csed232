#include <cmath>
#include <cstring>
#include <ios>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

int main() {
  char op[7]; // C style string for operator
  double operand1, operand2, result;
  cin >> op >> operand1;         // get operator and first operand
  if (strcmp(op, "square") == 0) // check unary operator
    result = operand1 * operand1;
  else if (strcmp(op, "sqrt") == 0)
    result = sqrt(operand1);
  else {             // case for binary operator
    cin >> operand2; // get second operand
    if (strcmp(op, "+") == 0)
      result = operand1 + operand2; // calculate addition
    else if (strcmp(op, "-") == 0)
      result = operand1 - operand2; // calculate substraction
    else if (strcmp(op, "*") == 0)
      result = operand1 * operand2; // calculate multiplication
    else if (strcmp(op, "/") == 0)
      result = operand1 / operand2; // calculate division
  }
  cout.precision(3); // set float output

  // Use std::fixed to specify format
  cout << std::fixed << result << endl;
  return 0;
}
