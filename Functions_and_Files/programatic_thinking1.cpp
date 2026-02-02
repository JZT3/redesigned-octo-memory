#include <iostream>

// Worst Version
int main()
{
  std::cout << "Enter an integer: ";

  int num { };
  std::cin >> num;

  num = num * 2;

  std::cout << "Double that number is: " << num << '\n';

  return 0;
}
/* 
This is a bad solution because before the assignment statement, num contains the 
user's input. After the assignment, it contains a different value.

In this solution we are overwriting the user's input by assigning a new value to
the input variable. If we wanted to extend this code, we have no access to the origonal
value.
*/
