/*
Avoid putting function or variable defintions in header files.

this results in the violation of the one-defintion rule in cases where the header file
is included in one or more source files.
 */
#include "header_files.h" // "" Tells the preprocessor this is a header file we wrote (tells the pp where to look)
#include <iostream>       // <> Tells the preprocessor this is a file  we did not write (OS or third party libraries)

int main()
{
  std::cout << "the sum of 6 and 7 is: " << add(6,7) << '\n';

  return 0;
}

/*
 In modern c++ there are 4 sets of header files.
 
 C++ specific      (new) <xxx>  identifiers placed in std namespace
 C++ compatibility (new) <cxx>  identifiers place in std namespace (required) or global (optional)
 C++ specific      (old) <xx.h> 
 C++ compatibility 


 */
