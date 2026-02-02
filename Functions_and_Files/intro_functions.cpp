// A function is a reusable sequnece of statements designed to do a prticular job.

/* 
Functions provide a way for us to split our code into small modular chunks that
are easiser to organize and test.
*/

#include <iostream>

void foo()
{
  main();   //Compile error: main not allowed to be called explicitly
  
  return 1; // Compile error: return value type does not match the function type

  /*
  A function must return a value unless the return type is void.
  A value-returning function must return a value of that type using a return statement,
  otherwise undefined behavior happens...
  */
}

void main()
{
  foo();    // Compiler error: main not allowed to have a non-int return type
}

int getValueFromUser()
{
  std::cout << "Enter an integer: ";
  int input {};
  std::cin >> input;

  return input; // Return the user value back to the caller

  /*
  Functions can only return a single value.
  */
}

int main() // You cannot overload functions distingushed by return type alone 
{

  int num { getValueFromUser() }; // Initialize num with the return value

  int x { getValueFromUser() }; // We can reuse functions...
  int y { getValueFromUser() };

  std::cout << num << " doubled is: " << num * 2 << '\n';
  std::cout << x << '+' << y << '=' << x + y << '\n';

  return 0; // Status code

  /* 
  By convention a status code of 0 means the program ran normally 
  The status code is passed back to the operating system.
  */


  /*
  There are 3 C++ standard return codes
  0

  these are preprocessor macros defined in the <cstdlib> header
  EXIT_SUCCESS
  EXIT_FAILURE  
  */
}

/*
If you need to use the return value of a function call more than once, initialize 
a variable with the return value, then use the variable as many times as needed.

Main is not always the first function that executes. 
Global variables are initialized prior to the execution of main.. 
*/
