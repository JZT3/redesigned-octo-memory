/*                    Uninitialized Variables

C++ does not automatically initialize most variables to a given value.
When a variable is not initialized, it is given a memory address to use to store data.
The default value of that variable is whatever garbage that happend to be in that mem address

Initialized   = The object is given a known value at the point of definition
Assignment    = The object is given a known value beyone the point of definiton
Uninitialized = The object has not been given a known value yet.

Uninitialization is a vestigial performance optimization from C. But these days typically
you should always initialize your variables ecause the cost is so minuscule.
*/

#include <iostream>

int main()
{
  int x; // Default initialization performs no actual initialization.
  // This is a really had mistake to debug!! 
  // This is why we prefere to always initialize your variables!

  std::cout << x << '\n'; // <--  assigning unused memory to x. Prints a random number everytime.

  /*
  This leads to the concept of "undefined behavior". UB
  UB is the resule of executing code whose behavrior is not well defined by the language.

  C++ doesnt have any rules for determining what should happen if you use a variable that has
  not been given a known value. 

                          Symptoms of Undefined Behavior
    Your program produces different results everytime it runs
    your program consistently produces the same incorrect result
    your program behaves inconsistently (sometimes correct, sometimes not)
    your program crashes, either immediately or later.
    your program works on some compilers, but not others
    your program works until you change some seemingly unrelated code
  */


    std::cout << sizeof(int) << '\n'; // implementation defined behavior 
    

  return 0;
}
