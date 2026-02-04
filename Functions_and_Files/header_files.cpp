/*
 Header Files are used to propagate a bunch of related foward delclarations into a code file

 They allow us to put our foward delclarations in one place 

 adding a header file is like adding  
*/

#include "header_files.h"

int add(int x, int y)
{
  return x + y;
}

/*
 Do not include *.cpp files 
 although the preprocessor will do this for you, its bad practice

  1) Can cause name collisions between source files
  2) In large projects it can be hard to avoid one definition rules
  3) Any changes in the *.cpp files will need to recompile which takes forever (header files take less time)
  4) breaks convention 

when using g++ we can use -I to specifiy include directory
g++ -o main -I./source/includes main.cpp

 */
