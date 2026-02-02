#include <iostream>

int add(int x, int y) // x and y are both parameters and local variables 
{
  int z { x + y }; // z is a local variable
  return z;
} // z,y,x destroyed here

/*
                        Lifetimes
Both variables x and y are created and initialized when the function is entered.
Variables within the function are initialzed at the point of definition.

Instatiated variables are destroyed in the opposite order of creation when the
closing } appears.

Creation, Initialization, and Destruction are guarantees. 
Objects must be created and iniatilized no later than the point of definition and
destroyed no earlier than the end of the curly braces.

The compiler has a lot of flexibility to determine when local variables are created 
and destroyed. see call_stack.cpp
*/

int main()
{
  int x { 6 }; 
  int y { 7 };

  // the Main x and y variables are distinct from the add functions x and y because of scope.


  std::cout << add(x,y) << '\n';
  // It is best practice to variables should be defined as close to their first use as possible.

  return 0;
}

/*
When a variable is needed within a function:
  use a function parameter when the caller will pass in the initial value for the variable
  as an argument

  otherwise use a local variable
*/
