/*
 There are generally two types of common errors
 Syntax Errors and Semantic Errors

 The compiler can detect your sytax erros.

 Semantic errors are logic errors, but the syntax is valid. Some, but not all sematic errors can be caught by the compiler
 Some semantic errors are only caught at runtime.
 */

#include <iostream>

int showNum(int x)
{ 
  return "hello"; // semantic error cannot convert string into int (must match return type)
  // This error is caught by the comiler
}

int add(int x, int y)
{
  return x - y; // Semantic error wrong operator used
                // error not caught by compiler or runtime
}


int main()
{ 
  int a { 10 };
  int b {  0 };

  5 = x; //Semantic error, cannot assign undecleared variable x
         //Thiss error is caught by the comiler

  std::cout << "Division result: " << a / b << '\n'; // Semantic error 10 / 0 
                                             // This error is only caught at run time

  int y; // no initializer provided
  std::cout << "your num: " << y << '\n'; // semantic error undefined behavior
                                  
  int c { 3 };
  int d { 5 };

  std::cout << "addition of nums: " << c << " " << d << "=" << add(c,d) << '\n';
              // Semantic error originating from function
  return 0;

  std::cout << "Hello World!" << '\n'; // Semantic error, code never executes after program exits
                                       
}

