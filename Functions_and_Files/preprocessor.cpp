/*
The preprocessor processes #include directives

once the preprocessor finishes procesessing the code it creates a translation unit. Only the output is compiled

The entire process is called translation
  preprocessing --> compiling --> linking 

phases 1 -- 4 == preprocessing
phases 5 -- 7 == compilation 

Directives tell the preprocessor to perform certain text manipulation tasks.

Macros
  Object-like Macros
    #define IDENTIFIER_NAME
    or
    #define IDENTIFIER_NAME substitution_text (avoid unless completly necessary)

  Function-like Macros (Unsafe!!)

*/

#include <iostream>

#define CIRCLE


int main()
{
  #ifndef CIRCLE
  std::cout << "circle" << '\n';
  #endif

  #ifndef SQUARE
  std::cout << "square" << '\n';
#endif

  #if 0 // exclude following block from being compiled
  std::cout << "triangle" << '\n';
  std::cout << "rhombus" << '\n';

  /*
  This technique is really good for 
  long multi-line comments
   */
#endif

  return 0;
}
