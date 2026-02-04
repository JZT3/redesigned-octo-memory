/*
Function Declarations (function prototypes) tell the compiler about the existence of an identifier
before actually defining it.

We can tell the compiler about the existence of functions before we define them.

*/

#include <iostream>

int add(int x, int y); //Forward declaration!
                      


int main()
{
  std::cout << "The sum is " << add(6,7) << '\n';

  return 0;
}

int add(int x, int y)
{
  return x + y;
}

/* 
  If you make a forward declaration, but never define the function and use it in your program
  you will get a linker error.

  Delcare --> Define --> Use

  

  You also can delcare/define variables in the scope of other functions. It can be a mistake to 
  accidentally define it twice!

Note: Functions that share an identifer, but have different params are considered different functions
This goes into function overloading.

 */
